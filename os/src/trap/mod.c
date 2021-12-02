#include <stdint.h>

#include <mod.h>

// trap entry
extern void __alltraps();

bool trap_init() {
  asm volatile("csrw stvec, %0" ::"r"(__alltraps));
  return true;
}

TrapContext* trap_handler(TrapContext* cx) {
  // read csr: scause, stval
  uint64_t scause;
  uint64_t stval;
  asm volatile("csrr %0, scause\n"
               "csrr %1, stval\n"
               : "=r"(scause), "=r"(stval));

  switch (scause)
  {
  case UserEnvCall:
    cx->sepc += 4;
    cx->reg[10] = syscall(cx.reg[17], cx.reg[10], cx.reg[11], cx.reg[12]);
    break;
  case StoreFault:
  case StorePageFault:
    DEBUG("[kernel] PageFault in application, core dumped.");
    run_next_app();
    break;
  case IllegalInstruction: 
    DEBUG("[kernel] IllegalInstruction in application, core dumped.");
    run_next_app();
    break;
  default:
    panic("Unsupported trap %ld, stval = %ld", scause, stval);
    break;
  }

  return cx;
}