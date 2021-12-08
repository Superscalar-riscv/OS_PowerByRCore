/**
 * syscall: system call  
 */

#include "syscall.h"
#include <stdio.h>

int64_t syscall(int id, uint64_t a0, uint64_t a1, uint64_t a2) {
  int64_t ret;
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


/**
 * 功能：将内存中缓冲区中的数据写入文件。
 * 参数：`fd` 表示待写入文件的文件描述符；
 * `buf` 表示内存中缓冲区的起始地址；
 * `len` 表示内存中缓冲区的长度。
 * 返回值：返回成功写入的长度。
 * syscall ID：64
 */
unsigned int sys_write(unsigned int fd, void *buf, unsigned int len) {
  return syscall(SYSCALL_WRITE, fd, (uint64_t)buf, len);
}

unsigned int sys_exit(unsigned int state) {
  printf("state=%d\n", state);
  return syscall(SYSCALL_EXIT, state, 0, 0);
}