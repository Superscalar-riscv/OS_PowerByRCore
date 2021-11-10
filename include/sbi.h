/**
 * Rust SBI 
 */

#include "common.h"

#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_SHUTDOWN 8

int64 sbi_call(uint64 id, uint64 a0, uint64 a1, uint64 a2);
void panic();
void console_putchar(char c);
void shutdown();
