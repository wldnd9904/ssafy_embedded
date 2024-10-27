#include <stdio.h>
#include <stdint.h>
int main() {

	uint32_t* IOBANK0 = (uint32_t*)0x400d0000;
	uint32_t* PADBANK0 = (uint32_t*)0x400f0000;

	uint32_t* GPIO2_CTRL;
    uint32_t* GPIO2_STATUS;
    uint32_t* GPIO20_CTRL;
    uint32_t* PADBANK0_GPIO2;
    uint32_t* PADBANK0_GPIO20;

    // uint32_t*에는 1을 더하면 4가 커진다. 즉
    // offset을 4로 나눠줘야 원하는 만큼 더해진다.
    GPIO2_CTRL = IOBANK0 + 0x014/4;
    GPIO2_STATUS = IOBANK0 + 0x010/4;
    GPIO20_CTRL = IOBANK0 + 0x0a4/4;
    PADBANK0_GPIO2 = PADBANK0 + 0x0c/4;
    PADBANK0_GPIO20 = PADBANK0 + 0x54/4;

    return 0;
}
