#include <stdint.h>
#include <stdio.h>
#include <context.h>

#define MAX_APP_NUM 3
#define USER_STACK_SIZE 4096*2
#define KERNEL_STACK_SIZE 4096*2
#define APP_BASE_ADDRESS 0x80400000
#define APP_SIZE_LIMIT 0x20000

typedef struct _AppManager
{
  uint64_t num_app;
  uint64_t current_app;
  uint64_t app_start[MAX_APP_NUM + 1];
}AppManager;


typedef struct _KernelStack
{
  uint8_t data[KERNEL_STACK_SIZE];
}KernelStack;

typedef struct _UserStack
{
  uint8_t data[USER_STACK_SIZE];
}UserStack;

uint64_t get_current_app();
void batch_init();
uintptr_t kernel_get_sp();
uintptr_t user_get_sp();
TrapContext* kernel_stack_push_context(TrapContext *cx);
void move_to_next_app();
void load_app(uint64_t app_id);
void run_next_app();

