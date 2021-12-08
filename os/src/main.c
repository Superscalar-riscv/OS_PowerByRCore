#include "printf.h"
#include "sbi.h"
#include "debug.h"
#include "batch.h"
#include "mod.h"

int main()
{
  clear_bss();
  LOG("[kernel] Hi! Welcome to OS!\n");
  // trap init
  trap_init();
  // batch init
  
  batch_init();
  // run next app
  run_next_app();
  return 0;
}
