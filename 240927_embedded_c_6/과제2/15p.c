#include <stdio.h>

int main() {
  int a = 10;
  char b = 'A';

  void* pa = &a;
  void* pb = &b;

  printf("%d\n", *(int*)pa);
  printf("%c\n", *(char*)pb);

  return 0;
}