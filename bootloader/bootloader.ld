ENTRY(bootloader_main)

SECTIONS
{
    . = 0x7C00;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}