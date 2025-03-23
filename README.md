<p align="center">
  🚧 REPO IS WORK IN PROGRESS 🚧
</p>

# swiOS

swiOS is a simple operating system for x86_64 architecture using UEFI. It is designed to demonstrate key OS concepts and provide a foundation for OS development.

## Features

- **Bootloader**: UEFI-compatible bootloader for x86_64 architecture
- **Kernel**: Modular kernel with memory management, interrupt handling, and device drivers
- **Memory Management**: Paging and heap allocation
- **Filesystem**: FAT32 filesystem support with basic operations (read, write, directory listing)
- **Device Drivers**:
  - PS/2 Keyboard driver with scan code mapping and key buffer
  - VGA Text Mode driver with color support and cursor management
- **Shell**: Simple command-line interface with basic commands
- **Build System**: Makefile-based build system and Python GUI for easy compilation

## System Requirements

- x86_64 architecture
- UEFI-compatible system (or QEMU with UEFI support)
- 64MB RAM (minimum)
- Development toolchain (see below)

## Development Requirements

To build and run swiOS, you'll need:

- **GCC Cross-Compiler** for x86_64-elf target
- **NASM** assembler
- **Make** build system
- **QEMU** x86_64 emulator
- **Python 3** with Tkinter (for the GUI build tool)
- **GRUB** tools (grub-mkrescue) for ISO creation
- **xorriso** for ISO image generation

## Building swiOS

### Using the GUI Tool

1. Run the Python GUI tool:
```
./scripts/build_gui.py
```

2. Configure build settings as needed
3. Click "Build" to compile the OS
4. Click "Run in QEMU" to test the OS in the emulator

## Project Structure

- `bootloader/` - UEFI bootloader source code
- `kernel/` - OS kernel source code
  - `kernel.c` - Main kernel entry point
  - `memory.c` - Memory management system
  - `interrupts.c` - Interrupt handling
  - `keyboard.c` - PS/2 keyboard driver
  - `video.c` - VGA text mode driver
  - `fs.c` - Filesystem implementation
- `os/` - OS components and userspace libraries
- `scripts/` - Build scripts and tools
  - `build_gui.py` - Python GUI build tool
- `Makefile` - Main build file

## Shell Commands

The swiOS shell supports the following commands:

- `help` - Show available commands
- `clear` - Clear the screen
- `memory` - Show memory usage information
- `ls` - List files in the current directory
- `cat <file>` - Display file contents
- `reboot` - Reboot the system

## Development Roadmap

- Network stack implementation
- USB support
- Graphics mode driver
- Window manager
- More filesystem types (ext2, NTFS)
- Multi-process support

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- [OSDev Wiki](https://wiki.osdev.org) - Invaluable resource for OS development
- [UEFI Specification](https://uefi.org/specifications) - Official UEFI documentation
