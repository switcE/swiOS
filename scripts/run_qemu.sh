#!/bin/bash
# Run the OS in QEMU using OVMF (UEFI firmware)
qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -drive format=raw,file=bootloader/bootloader.efi
