#include <stdio.h>

struct Node {
  int y;
  int x;
};

void abc(void* v) {
  struct Node val = *(struct Node*)v;

  printf("%d %d\n", val.y, val.x);
}

int main() {
  struct Node bbq = {.y = 10, .x = 20};
  abc(&bbq);
  return 0;
}