#include <printf.h>

int main() 
{
  printf("[user] Hello World\n");
  asm volatile("sret");
  return 0;
}