#!/bin/bash
# Build Bootloader
echo "Building Bootloader..."
cd ../bootloader
make clean && make
cd ../kernel

# Build Kernel
echo "Building Kernel..."
make clean && make
cd ../os

# Build OS
echo "Building OS..."
make clean && make
cd ..

echo "Build completed."
