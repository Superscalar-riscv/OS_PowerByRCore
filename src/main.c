#include "common.h"
#include "printf.h"
#include "sbi.h"
#include "debug.h"


int main()
{
  clear_bss();
  printf("Hello World\n");
  panic("main call panic\n");
  shutdown();
  return 0;
}