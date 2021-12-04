#include <syscall.h>
#include <debug.h>
#include <sbi.h>

int64_t syscall(uint64_t syscall_id, uint64_t a0, uint64_t a1, uint64_t a2) {
  int64_t ret;
  switch (syscall_id)
  {
  case SYSCALL_WRITE :
    ret = sys_write(a0, (void*)a1, a2);
    break;
  case SYSCALL_EXIT :
    ret = sys_exit(a0);
    break;
  default:
    panic("Unsuppored syscall id %ld\n", syscall_id);
    break;
  }
  return ret;
}


int64_t sys_write(uint64_t fd, void *buf, uint64_t len) {
  int64_t ret = -1;
  switch (fd)
  {
  case FD_STDOUT:
  {
    char *str = (char*)buf;
    for (size_t i = 0; i < len; ++i) {
      console_putchar(str[i]);
    }
    ret = (int64_t)len;
    break;
  }
  default:
    panic("Unsopported fd in sys_write!");
    break;
  }
  return ret;
}

int64_t sys_exit(uint64_t xstate) {
  DEBUG("[kernel] Application exited with code %ld\n", xstate);
  extern void run_next_app();
  run_next_app();
  return 0;
}