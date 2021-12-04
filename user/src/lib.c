
#include <printf.h>

// __attribute__((weak)) weak link character
__attribute__((weak)) int main() {
  printf("Cannot find main!");
  return 0;
}

extern char start_bss[], end_bss[];
void clear_bss() {
  for (char *i = (char*)start_bss; i < (char*)end_bss; i++)
    *i = 0;
}

// __attribute__((section("section_name")))，其作用是将作用的函数或数据放入指定名为"section_name"对应的段中
__attribute__((section(".text.entry"))) void _start()
{
  clear_bss();
  extern void exit(int exit_code);
  exit(main());
  printf("unreachable after sys_exit!");
}