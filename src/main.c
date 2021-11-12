#include "common.h"
#include "printf.h"
#include "sbi.h"
#include "debug.h"


int main()
{
  clear_bss();
  printf("Hello World\n");
  DEBUG("DEBUG TEST\n");
  panic("panic test\n");
  shutdown();
  return 0;
}
