#include <context.h>

TrapContext* app_init_context(void *entry, uint64_t sp) {
  uint64_t sstatus;
  asm volatile("csrr %0, status" : "=r"(sstatus) );

  // spp index = 8
  sstatus &= ~(1L << 8);
  // init stack
  TrapContext cx;
  cx.reg = { 0 },
  cx.sstatus = sstatus,
  cx.sepc = entry;
  return &cx;
}