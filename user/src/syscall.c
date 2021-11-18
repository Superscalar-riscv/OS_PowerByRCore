/**
 * syscall: system call  
 */

#include "syscall.h"

int syscall(int id, int a0, int a1, int a2) {
  int ret;
  asm volatile("ecall"
                : "={x10}" (ret)
                : "{x10}" (a0), "{x11}" (a1), "{x12}" (a2), "{x17}" (id)
                : "memory"
              );
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
  return syscall(SYSCALL_WRITE, fd, buf, len);
}

unsigned int sys_exit(unsigned int state) {
  return syscall(SYSCALL_EXIT, state, 0, 0);
}