#include <stdint.h>


uint64_t syscall(uint64_t id, uint64_t a0, uint64_t a1, uint64_t a2) {
  uint64_t ret;
  asm volatile (
      "mv a0, %1\n"
      "mv a1, %2\n"
      "mv a2, %3\n"
      "mv a7, %4\n"
      "ecall\n"
      "mv %0, a0\n"
      :"=r"(ret)
      :"r"(a0), "r"(a1), "r"(a2), "r"(id)
      :"memory", "a0", "a1", "a2", "a7");
  return ret;
}