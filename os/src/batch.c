#include <stdint.h>
#include <stdio.h>
#include <context.h>

#define MAX_APP_NUM 3

typedef struct _AppManager
{
  uint64_t num_app;
  uint64_t current_app;
  uint64_t app_start[MAX_APP_NUM + 1];
}AppManager;


AppManager app_manager;


extern void* _num_app;

AppManager init() {
  uintptr_t* num_app_ptr = (uintptr_t*)_num_app;
  uint64_t num_app = *num_app_ptr;
  uint64_t app_start[MAX_APP_NUM] = {0};

  AppManager new_manager;
  for (int i = 0 ; i < MAX_APP_NUM; ++i) {
    new_manager.app_start[i] = num_app_ptr + i;
  }
  new_manager.num_app = num_app;
  new_manager.current_app = 0;
  return new_manager;
}

#define USER_STACK_SIZE 4096*2
#define KERNEL_STACK_SIZE 4096*2

typedef struct _KernelStack
{
  uint8_t data[KERNEL_STACK_SIZE];
}KernelStack;

typedef struct _UserStack
{
  uint8_t data[USER_STACK_SIZE];
}UserStack;

// 
KernelStack kernel_stack = {0};
UserStack user_stack = {0};

uintptr_t kernel_get_sp() {
  return (uintptr_t)kernel_stack.data + KERNEL_STACK_SIZE;
}
uintptr_t user_get_sp() {
  return (uintptr_t)user_stack.data + KERNEL_STACK_SIZE;
}

// push context
TrapContext* kernel_stack_push_context(TrapContext *cx) 
{
  // push TrapContext to kernel stack
  TrapContext *context_ptr = (TrapContext *)kernel_get_sp() - 1;
  *context_ptr = *cx;
  return context_ptr;
}

void move_to_next_app() { 
  app_manager.current_app += 1; 
}

void load_app(uint64_t app_id) {
  printf("[kernel] Loading app_%ld\n", app_id);
  // clear icache
  asm volatile("fence.i");
  //clear app area
  
}

void run_next_app() {
  int current_app = app_manager.current_app;
  load_app(current_app);
  move_to_next_app();
  extern void __restore(uintptr_t sp);
  // app init
  TrapContext *app_contextcd = 
    app_init_context(app_manager.app_start[current_app], user_get_sp(),
    (TrapContext *)kernel_get_sp() - 1);
  // push app stack to kernel stack
  uintptr_t kernel_sp = kernel_stack_push_context(app_context);
  // restore
  __restore(kernel_sp);
  // error
  panic("Unreachable in batch::run_current_app!");
}