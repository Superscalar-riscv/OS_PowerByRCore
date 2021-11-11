
#include "printf.h"
#include "sbi.h"
#include "common.h"

#define LOG(...) \
  do { \
    printf(__VA_ARGS__); \
  } while (0)
  
#define DEBUG(fmt, ...) LOG("\33[1;34m[%s,%d,%s] " format "\33[0m\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define panic(fmt, ...) \ 
  do { \
    LOG(ANSI_LIGHT_BLUE"Panicked at [%s,%d,%s] " fmt ANSI_NONE"\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__); \
    shutdown(); \
  } while (0)
  