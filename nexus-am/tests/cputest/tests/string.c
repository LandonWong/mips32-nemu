// #include "trap.h"

// char *s[] = {
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
// 	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
// 	", World!\n",
// 	"Hello, World!\n",
// 	"#####"
// };

// char str1[] = "Hello";
// char str[20];

// int main() {
// 	nemu_assert(strcmp(s[0], s[2]) == 0);
// 	nemu_assert(strcmp(s[0], s[1]) == -1);
// 	nemu_assert(strcmp(s[0] + 1, s[1] + 1) == -1);
// 	nemu_assert(strcmp(s[0] + 2, s[1] + 2) == -1);
// 	nemu_assert(strcmp(s[0] + 3, s[1] + 3) == -1);

// 	nemu_assert(strcmp( strcat(strcpy(str, str1), s[3]), s[4]) == 0);

// 	nemu_assert(memcmp(memset(str, '#', 5), s[5], 5) == 0);

// 	return 0;
// }

#include "trap.h"

char *s[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	", World!\n",
	"Hello, World!\n",
	"#####"
};

char str1[] = "Hello";
char str[20];

unsigned cpy1[] ={0x73b72020,0x47acbaaa,0x2020c6a8,0xbaaac2c2,0xd0be5ea6,0xb4a52020};
unsigned cpy2[100];
int main() {
	// nemu_assert(strcmp(s[0], s[2]) == 0);
	// nemu_assert(strcmp(s[0], s[1]) == -1);
	// nemu_assert(strcmp(s[0] + 1, s[1] + 1) == -1);
	// nemu_assert(strcmp(s[0] + 2, s[1] + 2) == -1);
	// nemu_assert(strcmp(s[0] + 3, s[1] + 3) == -1);

	// nemu_assert(strcmp( strcat(strcpy(str, str1), s[3]), s[4]) == 0);

	// nemu_assert(memcmp(memset(str, '#', 5), s[5], 5) == 0);
	memcpy(cpy2,((char*)cpy1)+2,10);
	for(int i=0;i<10;i++) printf("%x ",((char*)cpy2)[i]);
	return 0;
}
