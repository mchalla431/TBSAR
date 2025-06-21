/* Simple linker script for LPC11xx (Cortex-M0, 32KB Flash, 8KB RAM) */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 32K
  RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 8K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
PROVIDE(__StackTop = _estack);

ENTRY(Reset_Handler)

SECTIONS
{
  .vectors :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame*)
    _etext = .;
    PROVIDE(__etext = .);
  } > FLASH

  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
  .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH

  .data : AT (ADDR(.text) + SIZEOF(.text))
  {
    _sdata = .;
    PROVIDE(__data_start__ = .);
    *(.data*)
    . = ALIGN(4);
    _edata = .;
    PROVIDE(__data_end__ = .);
  } > RAM

  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  .heap (NOLOAD) :
  {
    *(.heap*)
    . = ALIGN(8);
  } > RAM

  /* End of RAM */
  _end = .;
}
