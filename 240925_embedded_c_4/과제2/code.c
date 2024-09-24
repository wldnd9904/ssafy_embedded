#include <stdio.h>
#pragma pack(1)

typedef struct {
  int m1;
  char m2;
} BBQ;

int main() {
  BBQ bbq = {
      .m1 = 505,
      .m2 = 'z',
  };
  printf("%d %c\n", bbq.m1, bbq.m2);
  return 0;
}
