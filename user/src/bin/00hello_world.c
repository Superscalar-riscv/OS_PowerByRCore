#include <printf.h>

int main() 
{
  printf("Hello World\n");
  asm volatile("sret");
  return 0;
}