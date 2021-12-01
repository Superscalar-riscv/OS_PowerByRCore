#include <stdint.h>

// Exeception NO
#define InstructionMisaligned 0
#define InstructionFault 1
#define IllegalInstruction 2
#define Breakpoint 3
#define LoadMisaligned 4
#define LoadFault 5
#define StoreMisaligned 6
#define StoreFault 7
#define UserEnvCall 8
#define SupervisorEnvCall 9
#define MachineEnvCall 11
#define InstructionPageFault 12
#define LoadPageFault 13
#define StorePageFault 15

// Interrupt NO

// 
typedef struct _TrapContext
{
  uint64_t reg[32];
  uint64_t sstatus;
  uint64_t sepc;
}TrapContext;

TrapContext* app_init_context(uint64_t entry, uint64_t sp);