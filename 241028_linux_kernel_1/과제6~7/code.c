#include <stdint.h>
#include <stdio.h>
int main() {
  uint32_t GPIO2_CTRL = 0x000FFFFF;
  uint32_t GPIO2_STATUS = 0xFF7FFFFF;
  uint32_t GPIO20_CTRL = 0xFFFF0FFF;
  uint32_t PADBANK0_GPIO20 = 0x00FFFF00;
  uint32_t PADBANK0_GPIO2 = 0xFF00FF00;

  // 1. GPIO2_CTRL
  // INOVER 17:16 bit CLR
  GPIO2_CTRL &= ~(0b11 << 16);
  // FUNCSEL 4:0 bit CLR
  GPIO2_CTRL &= ~(0b11111);
  // FUNCSEL 4:0 bit 0x7 SET
  GPIO2_CTRL |= 0b111;

  // 2. GPIO2_STATUS
  // EVENT_LEVEL_HIGH 23:23 bit 추출
  // 아래쪽에 함

  // 3. GPIO20_CTRL
  // OEOVER 15:14 bit 0x3 SET
  GPIO20_CTRL &= ~(0b11 << 14);
  GPIO20_CTRL |= (0b11 << 14);
  // OUTOVER 13:12 bit 0x2 SET
  GPIO20_CTRL &= ~(0b11 << 12);
  GPIO20_CTRL |= (0b10 << 12);

  // 4. PADBANK0_GPIO20
  // DRIVE 5:4 0x1 SET
  PADBANK0_GPIO20 &= ~(0b11 << 4);
  PADBANK0_GPIO20 |= (0b01 << 4);
  // 5. PADBANK0_GPIO2
  // IE 6:6 bit 0x1 SET
  PADBANK0_GPIO2 |= (0b1 << 6);

  uint32_t INOVER = (GPIO2_CTRL >> 16) & 0b11;
  uint32_t FUNCSEL = GPIO2_CTRL & 0b11111;
  uint32_t EVENT_LEVEL_HIGH = (GPIO2_STATUS >> 23) & 0b1;
  uint32_t OEOVER = (GPIO20_CTRL >> 14) & 0b11;
  uint32_t OUTOVER = (GPIO20_CTRL >> 12) & 0b11;
  uint32_t DRIVE = (PADBANK0_GPIO20 >> 4) & 0b11;
  uint32_t IE = (PADBANK0_GPIO2 >> 6) & 0b1;
  return 0;
}
