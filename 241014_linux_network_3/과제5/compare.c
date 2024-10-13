#include <stdio.h>
#include <time.h>

int main() {
  clock_t aStart, aEnd, bStart, bEnd;
  int base = 2147483647;

  aStart = clock();
  int i = 100000000;
  while (i--) base << i;
  aEnd = clock();

  printf("[<< time : %lfs]\n", (double)(aEnd - aStart) / CLOCKS_PER_SEC);

  bStart = clock();
  i = 100000000;
  while (i--) base % i;
  bEnd = clock();

  printf("[%% time : %lfs]\n", (double)(bEnd - bStart) / CLOCKS_PER_SEC);

  return 0;
}
