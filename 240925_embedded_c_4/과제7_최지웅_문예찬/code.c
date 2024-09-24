#include <stdint.h>
#include <stdio.h>
#pragma pack(1)

union parser {
  struct {
    uint16_t weight;
    struct {
      uint16_t pass;
      uint16_t salary;
      uint8_t food[4];
      uint8_t drink[4];
    } unique_id;
  } field;
};

int main() {
  FILE* fp = fopen("binary", "r");
  uint8_t buf[14];  // 16 + 96 = 112 bit / 8 = 14 Byte
  fread(buf, 1, 14, fp);
  fclose(fp);

  union parser* p = (union parser*)buf;
  printf("weight: %d\n", p->field.weight);

  printf("pass: %d\n", p->field.unique_id.pass);

  printf("salary: %d\n", p->field.unique_id.salary);

  printf("food: ");
  for (int i = 3; i >= 0; --i) printf("%c", p->field.unique_id.food[i]);
  printf("\n");

  printf("drink: ");
  for (int i = 3; i >= 0; --i) printf("%c", p->field.unique_id.drink[i]);
  printf("\n");

  return 0;
}
