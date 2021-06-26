# demo68k
MiSTer use of 68000 cpu core and targetting C code.  

If you wish to build your own rom you will need a compiler for the Motorola 68000 CPU.  
There is a sample batch file included for building on windows although the steps should be the same on Linux.

A linker script .ld file allows gcc to place the reset vector table, rom, and ram locations.  If you change the 
addressing you will have to update it.

Be aware that creating the Intel hex file requires the addresses are in words and not byte offsets.  Quartus 17 will not load
16 bit hex files correctly unless there is only one 16 bit word per line in the hex file.
