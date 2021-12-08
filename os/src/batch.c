#include "batch.h"
#include <debug.h>
#include <string.h>

// 
AppManager app_manager;
// 内核栈和用户栈， 按4KB对齐
KernelStack kernel_stack __attribute__ ((aligned(4096)));
UserStack user_stack __attribute__ ((aligned(4096)));

uint64_t get_current_app() {
  return app_manager.current_app;
}

uintptr_t kernel_get_sp() {
  return (uintptr_t)kernel_stack.data + KERNEL_STACK_SIZE;
}
uintptr_t user_get_sp() {
  return (uintptr_t)user_stack.data + KERNEL_STACK_SIZE;
}

void printAppInfo() {
  INFO("The Apps Num: %d\n", app_manager.num_app);
  for (size_t i = 0; i < app_manager.num_app; i++) {
    INFO("App[%d] => [0x%lx, 0x%lx]\n", i, app_manager.app_start[i], app_manager.app_start[i+1]);
  }
}

// defined at link_app.S
void batch_init() {
  extern uint64_t _num_app;
  uint64_t* num_app_ptr = &_num_app;
  DEBUG("batch_init: num_app: %d\n", *num_app_ptr);
  for (int i = 0 ; i < MAX_APP_NUM + 1; ++i) {
    app_manager.app_start[i] = num_app_ptr[i + 1];
  }
  app_manager.num_app = *num_app_ptr;
  app_manager.current_app = 0;
  // print all apps info
  printAppInfo();
}

// push context to kernel stack
TrapContext* kernel_stack_push_context(TrapContext *cx) 
{
  TrapContext *context_ptr = (TrapContext *)kernel_get_sp() - 1;
  *context_ptr = *cx;
  return context_ptr;
}

void move_to_next_app() { 
  app_manager.current_app += 1; 
}

void load_app(uint64_t app_id) {
  if (app_id >= app_manager.num_app) {
    panic("All application completed!\n");
  }
  INFO("[kernel] Loading app_%ld\n", app_id);
  // clear icache
  asm volatile("fence.i");
  //clear app area
  for (size_t i = 0; i < APP_SIZE_LIMIT / 8; ++i) {
    *(uint64_t*)(APP_BASE_ADDRESS + i) = 0;
  }
  // init app code
  uint8_t* app_start_addr = (uint8_t*)app_manager.app_start[app_id];
  uint64_t app_len = (uint8_t*)app_manager.app_start[app_id + 1] - app_start_addr;
  //
  memcpy((void*)APP_BASE_ADDRESS, (void*)app_start_addr, app_len);
}

// defined at trap.S
extern void __restore(uintptr_t sp);
void run_next_app() {
  int current_app = get_current_app();
  load_app(current_app);
  move_to_next_app();
  
  // app init and push app stack to kernel stack
  TrapContext* kernel_sp = kernel_stack_push_context(app_init_context(
    (void*)APP_BASE_ADDRESS, user_get_sp(),
    (TrapContext *)kernel_get_sp() - 1));
  // restore
  __restore((uintptr_t)kernel_sp);
  // error
  panic("Unreachable in batch::run_current_app!");
}