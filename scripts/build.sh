#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Build the bootloader
echo "Building bootloader..."
make -C bootloader

# Build the kernel
echo "Building kernel..."
make -C kernel

# Build the OS
echo "Building OS..."
make -C os

# Combine bootloader and kernel into a single binary
echo "Combining bootloader and kernel..."
cat bootloader/bootloader.bin kernel/kernel.bin > os-image.bin

echo "Build complete. OS image is os-image.bin"