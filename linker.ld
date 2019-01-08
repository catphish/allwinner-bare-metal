SECTIONS
{
  . = 0x4e000000;
  .text : {
    boot.o(.text)
    *(.text)
  }
  .bss : {
    _bstart = . ;
    *(.bss); *(COMMON);
     _bend = . ;
  }
}
