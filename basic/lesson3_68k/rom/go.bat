; toolchain available 
; https://gnutoolchains.com/m68k-elf/

m68k-elf-gcc -Wall -nostdlib -nodefaultlibs -fomit-frame-pointer -m68000 -c test.c
m68k-elf-ld -T 68k.ld test.o
m68k-elf-objcopy -I coff-m68k -O binary a.out test.bin

; disassembly can be generated using
; m68k-elf-objdump -d a.out