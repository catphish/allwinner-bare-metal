SECTIONS
{
  .text : {
    boot.o(.text)
    *(.text)
  }
}
