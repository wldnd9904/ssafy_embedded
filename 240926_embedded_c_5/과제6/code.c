#include <stdio.h>
#define _ABC_

#ifdef _ABC_
#define BBQ
#define KFC
#else
#define _ABC_
#endif

#ifndef KFC
#define KFC
#endif

int main() {
#ifdef BBQ
  printf("최지웅\n");
#endif
  return 0;
}