#include <stdint.h>
#include <stdio.h>

union parser {
  struct {
    uint8_t a : 2;
    uint8_t b : 2;
    uint8_t c : 2;
    uint8_t d : 2;
  } field;
};

int main() {
  uint8_t data = 0b11100001;

  union parser* p = (union parser*)&data;

  printf("data: 0x%X\n", data);
  printf("a: 0x%X\n", p->field.a);
  printf("b: 0x%X\n", p->field.b);
  printf("c: 0x%X\n", p->field.c);
  printf("d: 0x%X\n", p->field.d);

  return 0;
}
