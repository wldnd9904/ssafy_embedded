#include <stdint.h>
#include <stdio.h>

union parser {
  uint64_t g;
  uint8_t buf[8];
};

int main() {
  uint64_t g = 0xABCD12345678CD01;

  union parser* p = (union parser*)&g;

  for (int i = 0; i < 8; i++) printf("%02X", p->buf[i]);
  return 0;
}
