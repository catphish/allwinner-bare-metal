SECTIONS
{
  . = 0x4e000000;
  .text : {
    boot.o(.text)
    *(.text)
  }
}
