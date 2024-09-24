#include <stdint.h>
#include <stdio.h>

union parser {
  struct {
    uint8_t header[3];
    uint8_t body[2];
    uint8_t tail[2];
  } field;
};

int main() {
  uint8_t data[7] = {0xAB, 0xCD, 0xEF, 0x12, 0x09, 0xAF, 0xAF};

  union parser* p = (union parser*)data;

  printf(" header: ");
  for (int i = 0; i < 3; i++) printf("%02X", p->field.header[i]);

  printf("\n body: ");
  for (int i = 0; i < 2; i++) printf("%02X", p->field.body[i]);

  printf("\n tail: ");
  for (int i = 0; i < 2; i++) printf("%02X", p->field.tail[i]);
  return 0;
}
