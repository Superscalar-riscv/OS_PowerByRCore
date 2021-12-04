#ifndef __SBI_H__
#define __SBI_H__
/**
 * Rust SBI 
 */

#include <stdint.h>
#include "common.h"


#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_SHUTDOWN 8

int64_t sbi_call(uint64_t id, uint64_t a0, uint64_t a1, uint64_t a2);
void console_putchar(char c);
void shutdown();
void clear_bss();

#endif