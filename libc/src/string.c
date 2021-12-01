#include <string.h>

size_t strlen(const char *s) {
  int num = 0;
  for (int i = 0; s[i] != '\0'; i++)
    num += 1;
  return num;
}

char *strcpy(char* dst,const char* src) {
  char* s = dst;
  while ((*s++ = *src++) != '\0');
  
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  char* start = dst;
	while (n && (*dst++=*src++))
		n--;
	if(n)
		while (--n)
			*dst++='\0';

  return start;
}

char* strcat(char* dst, const char* src) {
  char *tmp = dst;
  while (*dst)
    dst++;
  while ((*dst++ = *src++) != '\0');

  return tmp;
}

int strcmp(const char* s1, const char* s2) {
  while(*s1 && (*s1 == *s2)){
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  for (; 0 < n; ++s1, ++s2, --n)
  {
    if(*s1 != *s2)
      return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
    else if(*s1 == '\0')
      return 0;
  }
  return 0;
}

void* memset(void* v, int c, size_t n) {
  const unsigned char uc = c;    //unsigned char占1字节，意味着只截取c的后八位
	unsigned char *su;
	for(su = v; 0 < n; ++su,--n)
		*su = uc;
	return v;
}

void* memmove(void* dst,const void* src,size_t n) {
  char* sc1;
  const char* sc2;

  sc1 = dst;  sc2 = src;
  if(sc2 < sc1 && sc1 < sc2 + n)
    for(sc1 += n, sc2 += n; 0 < n; --n)
      *--sc1 = *--sc2;
  else
    for (; 0 < n; --n)
      *sc1++ = *sc2++;
    
  return dst;
}

void* memcpy(void* out, const void* in, size_t n) {
  char* su1;
  const char* su2;
  for(su1 = out, su2 = in; 0 < n; ++su1, ++su2, --n)
    *su1 = *su2;
  return out;
}

/* 
确定两个相等长度的字符序列的字符是否一一对应
 */
int memcmp(const void* s1, const void* s2, size_t n) {
  const unsigned char *su1, *su2;

  for(su1 = s1, su2 = s2; 0 < n; ++su1, ++su2, --n)
    if(*su1 != *su2)
      return ((*su1 < *su2) ? -1 : +1);
  return 0;
}