#include <stdint.h>

#define FD_STDOUT 1

uint64_t sys_write(uint64_t fd, void *buf, uint64_t len) {
  switch (fd)
  {
  case FD_STDOUT:
    printf("%s", buf);
    break;
  
  default:
    panic("Unsopported fd in sys_write!");
    break;
  }
}

uint64_t sys_exit(uint64_t xstate) {
  printf("[kernel] Application exited with code %ld\n", xstate)
  run_next_app();
}