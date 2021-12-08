#ifndef _SYSCALL_H_
#define _SYSCALL_H_
#include <stdint.h>

// syscall event id
#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

int64_t syscall(int id, uint64_t a0, uint64_t a1, uint64_t a2);

void write(int fd, void *buf, int len);

void exit(int exit_code);
/**
 * 功能：将内存中缓冲区中的数据写入文件。
 * 参数：`fd` 表示待写入文件的文件描述符；
 * `buf` 表示内存中缓冲区的起始地址；
 * `len` 表示内存中缓冲区的长度。
 * 返回值：返回成功写入的长度。
 * syscall ID：64
 */
unsigned int sys_write(unsigned int fd, void *buf, unsigned int len);

unsigned int sys_exit(unsigned int state);

#endif