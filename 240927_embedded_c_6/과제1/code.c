#include <stdio.h>

int main() {
  int p = 127, q = 255;
  int *bbq = &p, *kfc = &q;

  *bbq = 128;
  *kfc = 256;

  printf("%d %d", *bbq, *kfc);
  return 0;
}