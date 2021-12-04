#ifndef __MOD_H__
#define __MOD_H__

#include <context.h>

//
int trap_init();
TrapContext* trap_handler(TrapContext* cx);

#endif