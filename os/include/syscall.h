#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

#define FD_STDOUT 1

int64_t syscall(uint64_t syscall_id, uint64_t a0, uint64_t a1, uint64_t a2);
int64_t sys_write(uint64_t fd, void *buf, uint64_t len);
int64_t sys_exit(uint64_t xstate);

#endif