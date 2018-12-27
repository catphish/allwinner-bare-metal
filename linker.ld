SECTIONS
{
  . = 0x4d000000;
  .text : {
    boot.o(.text)
    *(.text)
  }
}
