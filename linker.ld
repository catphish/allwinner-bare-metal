SECTIONS
{
  .text : {
    . = 0x0;
    boot.o(.text)
    . = 0x30;
    *(.text)
  }
}
