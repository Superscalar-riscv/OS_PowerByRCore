#include "syscall.h"
#include <stdio.h>

#define STDOUT 1


void write(int fd, void *buf, int len) {
  sys_write(fd, buf, len);
}

void exit(int exit_code) {
  printf("exit\n");
  sys_exit(exit_code);
}