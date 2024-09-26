#include <stdio.h>

int main() {
  volatile int a = 10;
  a = 20;
  a = 30;
  a = 40;
  printf("%d", a);
  return 0;
}