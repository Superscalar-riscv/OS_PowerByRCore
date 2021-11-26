#include<stdint.h>

#define MAX_APP_NUM 16


struct AppManager
{
  uint64_t num_app;
  uint64_t current_app;
  uint64_t app_start[MAX_APP_NUM + 1];
};
