#include "trap.h"

volatile unsigned x = 0xffffffff;
volatile unsigned char buf[30]= {0xaa,0xb6,0x69,0xab,0xd7,0xa4,0xad,0x20,0x20,0x20,0x20,0xaa,0xb6,0x69,0xab,0xd7,0xa4,0xad,0x20,0x20,0x20,0x20};
unsigned char dst[30]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

int main() {

	for(int i = 0; i < 4; i++) {
		//*((volatile unsigned*)(buf + 3)) = 0xaabbccdd;

		x= *(volatile unsigned*)(dst+3+4*i) = *((volatile unsigned*)(buf + 3 + 4*i));
		for(int i=0;i<30;i++) printf("%x ",dst[i]);
		printf("\n");
		//nemu_assert(x == 0xaabbccdd);

		buf[0] = buf[1] = buf[2] = 0;
	}

	return 0;
}
