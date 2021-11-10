#include "common.h"
#include "printf.h"
#include "sbi.h"

extern char sbss[];
extern char ebss[];

void clear_bss() {
  // for (char *i = &sbss; i < &ebss; i++)
  //   *i = 0;
}



void _start() {
  // 
  clear_bss();
  printf("Hello World\n");
  shutdown();
}

int main()
{
    //printf("Hello World\n");
    return 0;
}