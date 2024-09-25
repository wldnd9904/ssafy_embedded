#include <stdio.h>
// #define DEBUG
#define RELEASE

#ifdef DEBUG
#define CAMERA
#endif

#ifdef RELEASE
#define GPS
#endif

int main() {
#ifdef CAMERA
  printf("hifaker\n");
#endif
#ifdef GPS
  printf("BBQ\n");
#endif
  return 0;
}