#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Check if the OS image exists
if [ ! -f os-image.bin ]; then
  echo "OS image not found. Please build the project first."
  exit 1
fi

# Run the OS image in QEMU
echo "Running OS image in QEMU..."
qemu-system-x86_64 -drive format=raw,file=os-image.bin