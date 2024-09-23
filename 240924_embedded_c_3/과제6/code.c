#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int a = 0xABCDEF12;
  long long b = 0xFFFF5555AAAA5555;
  struct Node {
    int a, b;
  };
  struct Node c = {0x77665544, 0x11223344};
  return 0;
}
