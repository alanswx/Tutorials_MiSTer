#include <stdio.h>
#include <stdlib.h>

#define kSize 1024*16

unsigned char b[kSize];

main(int argc, char *argv[])
{
	int i;
	char *bs;

	if (1 || argc > 1 && argv[1][0] == '-' && argv[1][1] == 'c') {
		// case
		read(0, b, kSize);

		printf("  // centipede\n");
		printf("  case (a)\n");
		for (i = 0; i < kSize; i++) {
			printf("\t14'h%03x: q = 8'h%02x; // 0x%03x\n", i, b[i], i);
		}
		printf("  endcase\n");
	} else {
		// initial block
		printf("initial begin\n");
		printf("\t// centipede\n");

		read(0, b, 8192);
		for (i = 0; i < 2048; i++) {
			printf("\trom[%d] = 8'h%02x; // 0x%04x\n", i, b[i], i);
		}
		
		printf("end\n");
	}

	exit(0);
}
