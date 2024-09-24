#include <stdio.h>
#pragma pack(1)

struct KFC {
  int m1;
  char m2;
  int m3[5];
};

int main() {
  struct KFC kfc = {.m1 = 123, .m2 = 'P', .m3 = {5, 4, 3, 2, 1}};
  printf("%d %c\n", kfc.m1, kfc.m2);
  for (int i = 0; i < 5; i++) {
    printf("%d ", kfc.m3[i]);
  }
  return 0;
}
