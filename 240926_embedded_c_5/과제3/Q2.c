#include <stdio.h>
// #define DEBUG

#ifdef DEBUG
#define RELEASE
#endif

#ifdef RELEASE
int main() {
  int a = 1000;
  printf("%d", a);
  return 0;
}
#define ABC
#endif

#undef ABC
#ifdef ABC
int main() {
  int a = 2000;
  printf("%d", a);
  return 0;
}
#endif