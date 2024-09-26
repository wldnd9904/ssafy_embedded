#include <stdio.h>

void abc(void* v) { printf("%d\n", *(int*)v); }

int main() {
  int x = 10;
  abc(&x);
  return 0;
}