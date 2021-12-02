#include "batch.h"

AppManager app_manager;

uint64_t get_current_app() {
  return app_manager.current_app;
}

extern void* _num_app;

void batch_init() {
  uintptr_t* num_app_ptr = (uintptr_t*)_num_app;
  uint64_t num_app = *num_app_ptr;
  uint64_t app_start[MAX_APP_NUM] = {0};


  for (int i = 0 ; i < MAX_APP_NUM; ++i) {
    app_manager.app_start[i] = num_app_ptr + i;
  }
  app_manager.num_app = num_app;
  app_manager.current_app = 0;

}


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
  if (app_id >= app_manager.num_app) {
    panic("All application completed!");
  }
  printf("[kernel] Loading app_%ld\n", app_id);
  // clear icache
  asm volatile("fence.i");
  //clear app area
  for (size_t i = 0; i < APP_SIZE_LIMIT / 8; ++i) {
    *(uint64_t*)(APP_BASE_ADDRESS + i) = 0;
  }
  (uint8_t*) app_start_addr = (uint8_t*)app_manager.app_start[app_id];
  uint64_t len = (uint8_t*)app_manager.app_start[app_id + 1] - app_start_addr;
  //
  memcpy((void*)APP_BASE_ADDRESS, (void*)app_start_addr, len);
}

extern void __restore(uintptr_t sp);
void run_next_app() {
  int current_app = get_current_app();
  load_app(current_app);
  move_to_next_app();
  
  // app init and push app stack to kernel stack
  uintptr_t kernel_sp = kernel_stack_push_context(app_init_context(
    APP_BASE_ADDRESS, user_get_sp(),
    (TrapContext *)kernel_get_sp() - 1));
  // restore
  __restore(kernel_sp);
  // error
  panic("Unreachable in batch::run_current_app!");
}