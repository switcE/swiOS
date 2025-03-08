/* Bootloader linker script stub */
OUTPUT_FORMAT("efi-app-x86_64")
ENTRY(efi_main)
SECTIONS {
  . = 0x100000;
  .text : { *(.text*) }
  .data : { *(.data*) }
  .bss  : { *(.bss*) }
}
