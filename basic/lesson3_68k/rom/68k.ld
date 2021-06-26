MEMORY
{
  rom      (rx)  : ORIGIN = 0x000000, LENGTH = 0x02000
  ram      (rwx) : ORIGIN = 0x100000, LENGTH = 0x02000
  vram     (rw)  : ORIGIN = 0x800000, LENGTH = 0x25800  
}

STACK_SIZE = 0x100;

/* Section Definitions */
SECTIONS
{
    .text :
    {
        KEEP(*(.vectors .vectors.*))
        _stext = .;
        *(.text.*)
        *(.rodata.*)
        _etext = .;
    } > rom

    .bss (NOLOAD) :
    {
        _sbss = . ;
        *(.bss .bss.*)
        *(COMMON)
        _ebss = . ;
    } > ram

    .data :
    {
        _sdata = .;
        *(.data*);
        _edata = .;
    } > ram AT >rom

    /* stack section */
    .stack (NOLOAD):
    {
        _sstack = .;
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > ram

    .dummy_vram :
    {
        _vram = .;
        KEEP(*(.dummy_vram))
    } > vram
    
    _end = . ;
}