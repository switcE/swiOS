<p align="center">
  🚧 REPO IS WORK IN PROGRESS 🚧
</p>

# swiOS

## Overview
wiOS is a simple operating system for the x86_64 architecture using UEFI. The bootloader is built using nyu-efi, the kernel is written in C, and higher-level OS components (shell and file wrapper) are written in C++.

## Project Structure
- **/bootloader**: UEFI bootloader.
- **/kernel**: Kernel code including video output, memory management (bump allocator), interrupt handling, a basic FAT32 driver (using a simulated disk image), and a stub USB keyboard driver.
- **/os**: Higher-level OS code (main logic, shell, file operations) in C++.
- **/include**: Header files.
- **/lib**: Utility libraries for string and memory functions.
- **/scripts**: Build and run scripts.
- **Makefile**: Root Makefile to build all components.

## Building
Run the build script from the `/scripts` directory `./build.sh`

## Running in QEMU
Run the OS:
`./run_qemu.sh`
