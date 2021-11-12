
#include "printf.h"
#include "sbi.h"
#include "common.h"

#define LOG(...) \
  do { \
    printf(__VA_ARGS__); \
  } while (0)
  
#define DEBUG(fmt, ...) LOG( ANSI_RED "[%s,%d,%s] " fmt ANSI_NONE, \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define panic(fmt, ...) \
  do { \
    LOG(ANSI_LIGHT_BLUE"Panicked at [%s,%d,%s] " fmt ANSI_NONE, __FILE__, __LINE__, __func__, ## __VA_ARGS__); \
    shutdown(); \
  } while (0)
