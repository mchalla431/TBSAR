/*
 * Linker script for NXP LPC11C24 microcontroller
 * 
 * Memory layout:
 * - Flash: 32KB (0x00000000 - 0x00007FFF)
 * - RAM: 8KB (0x10000000 - 0x10001FFF)
 * - CAN RAM: 2KB (0x50000000 - 0x500007FF)
 */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 32K
    RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 8K
    CANRAM (rw): ORIGIN = 0x50000000, LENGTH = 2K
}

/* Stack size - adjust as needed */
STACK_SIZE = 0x200; /* 512 bytes stack */

/* Entry point */
ENTRY(Reset_Handler)

SECTIONS
{
    /* Vector table and startup code */
    .text :
    {
        KEEP(*(.vectors))
        *(.text*)
        *(.init*)
        *(.fini*)
        *(.rodata*)
        . = ALIGN(4);
        __etext = .;
    } > FLASH

    /* Initialized data section */
    .data : AT (__etext)
    {
        __data_start__ = .;
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM

    /* Uninitialized data section */
    .bss :
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    /* Stack section */
    .stack :
    {
        . = ALIGN(8);
        _stack_start = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _stack_end = .;
    } > RAM

    /* Heap section (optional - only allocate remaining space) */
    .heap :
    {
        __heap_start__ = .;
        __heap_end__ = _stack_start;
        end = __heap_start__;  /* Provide 'end' symbol for newlib */
        _end = __heap_start__; /* Alternative name */
    } > RAM

    /* CAN message objects in CAN RAM */
    .canram (NOLOAD) :
    {
        *(.canram*)
    } > CANRAM

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}

/* Provide stack pointer */
__StackTop = ORIGIN(RAM) + LENGTH(RAM);