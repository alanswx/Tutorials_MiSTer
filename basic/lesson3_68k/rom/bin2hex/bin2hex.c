#include <stdio.h>
#include <stdlib.h>

void ConvertFile(char *srcname, char *dstname)
{
    int count,checksum;
    int offs = 0;
    int offsh, offsl;
    FILE *src,*dst;
    unsigned char buffer[16];

    src = fopen(srcname,"rb");
    if (ferror(src))
    {
        char errbuf[256] = "";
        perror(errbuf);
        printf("%s\n", errbuf);
        exit(0);
    }

    dst = fopen(dstname,"w");

    count = fread(buffer, 1, 2, src);

    while ( count > 0 ) {
        offsh = ( offs >> 8 ) & 0xff ;
        offsl = offs & 0xff ;
        // value of each hex digit in the output line
        checksum = 2 + offsh + offsl + buffer[0] + buffer[1];

        if ( count == 1 ) {
                // always write 16 bits worth
                buffer[1]=0;
        }
        // 
        fprintf(dst,":02%02X%02X00%02X%02X%02X\n", offsh, offsl, buffer[0], buffer[1], (65536-checksum) & 0xff);  

        offs++;  // one 16 bit word
        // read more
        count = fread(buffer, sizeof(unsigned char), 2, src);
    }

    fprintf(dst,":00000001FF\n");

    fclose(src);
    fclose(dst);
}

int main (int argc, char **argv )
{

    if ( argc == 0 ) {
        printf("usage: bin2hex test.bin test.hex");
        exit(0);
    }

    ConvertFile(argv[1],argv[2]);
}