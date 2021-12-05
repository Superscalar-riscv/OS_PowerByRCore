#ifndef __DEBUG_H__
#define __DEBUG_H__
#include "printf.h"
#include "sbi.h"
#include "common.h"

#define LOG(...) \
  do { \
    printf(__VA_ARGS__); \
  } while (0)
  

#define ERROR(fmt, ...) LOG( ANSI_RED "[%s,%d,%s] " fmt ANSI_NONE, \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define WARN(fmt, ...) LOG( ANSI_YELLOW "[%s,%d,%s] " fmt ANSI_NONE, \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define INFO(fmt, ...) LOG( ANSI_LIGHT_BLUE fmt ANSI_NONE, ## __VA_ARGS__)

#define DEBUG(fmt, ...) LOG( ANSI_LIGHT_GREEN fmt ANSI_NONE, ## __VA_ARGS__)

#define TRACE(fmt, ...) LOG( ANSI_LIGHT_GRAY "[%s,%d,%s] " fmt ANSI_NONE, \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define panic(fmt, ...) \
  do { \
    LOG(ANSI_LIGHT_RED "Panicked at [%s,%d,%s] " fmt ANSI_NONE, __FILE__, __LINE__, __func__, ## __VA_ARGS__); \
    shutdown(); \
  } while (0)


#endif