#include "sbi.h"
#include "common.h"
#include "debug.h"
#include <stdarg.h>

// 
int64 sbi_call(uint64 id, uint64 a0, uint64 a1, uint64 a2) {
  uint64 ret;
  asm volatile (
      "mv a0, %1\n"
      "mv a1, %2\n"
      "mv a2, %3\n"
      "mv a7, %4\n"
      "ecall\n"
      "mv %0, a0\n"
      :"=r"(ret)
      :"r"(a0), "r"(a1), "r"(a2), "r"(id)
      :"memory", "a0", "a1", "a2", "a7"
  );
  return ret;
}

extern char sbss[];
extern char ebss[];

void clear_bss() {
  for (char *i = (char*)sbss; i < (char*)ebss; i++)
    *i = 0;
}

// void panic(const char *fmt, ...) {
//   Log(fmt,  ## __VA_ARGS__);
//   shutdown();
// }

void console_putchar(char c) {
  sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

void shutdown() {
  sbi_call(SBI_SHUTDOWN, 0, 0, 0);
  //panic("It should shutdown!");
}
