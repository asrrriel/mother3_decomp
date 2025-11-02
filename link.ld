ENTRY(_start)

MEMORY
{
  rom (rx) : ORIGIN = 0x08000000, LENGTH = 32M
  iwram (wx) : ORIGIN = 0x03000000, LENGTH = 32K
  ewram (wx) : ORIGIN = 0x02000000, LENGTH = 256K
}

SECTIONS
{
  . = ORIGIN(rom);
  .hdr :
  {
    KEEP(*(.hdr))
  } > rom

  . = 0x080000C0;
  .text ALIGN(4) :
  {
    KEEP(*(.text.startup))
    *(.text*)
    *(.rodata*)
  } > rom

  .data ALIGN(4) :
  {
    *(.data*)
  } > ewram AT > rom

  . =0x03000000;

  .bss ALIGN(4) (NOLOAD) :
  {
    *(.bss*)
    *(COMMON)
  } > iwram
}