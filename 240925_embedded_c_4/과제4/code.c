#include <stdint.h>
#include <stdio.h>

union parser {
  struct {
    uint8_t header[5];
    uint8_t body[4];
    uint8_t tail[2];
  } field;
};

int main() {
  uint8_t data[11] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab,
                      0xcd, 0xef, 0x98, 0x76, 0x54};
  union parser* p = (union parser*)data;

  printf(" header: ");
  for (int i = 0; i < 5; i++) printf("%02X", p->field.header[i]);

  printf("\n body: ");
  for (int i = 0; i < 4; i++) printf("%02X", p->field.body[i]);

  printf("\n tail: ");
  for (int i = 0; i < 2; i++) printf("%02X", p->field.tail[i]);
  return 0;
}
