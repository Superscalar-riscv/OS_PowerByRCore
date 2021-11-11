
#include "printf.h"
#include "sbi.h"


#define DEBUG(...) \
  do { \
    printf(__VA_ARGS__); \
  } while (0)
  


#define panic(fmt, ...) \ 
  do { \
    DEBUG("\33[1;34m Panicked at [%s,%d,%s] " fmt "\33[0m\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__); \
    shutdown(); \
  } while (0)
  