#include <context.h>

TrapContext* app_init_context(void *entry, uint64_t sp, TrapContext* cx) {
  uint64_t sstatus;
  asm volatile("csrr %0, status" : "=r"(sstatus) );

  // spp index = 8
  sstatus &= ~(1L << 8);
  // init stack
  for (int i = 0; i < 32; ++i) {
    cx->reg[i] = 0;
  }
  
  cx->reg[2] = sp;
  cx->sstatus = sstatus;
  cx->sepc = entry;
  return cx;
}