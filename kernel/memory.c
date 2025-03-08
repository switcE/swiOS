#include "memory.h"
#include "lib.h"

// A simple bump allocator for kernel memory management
static unsigned long heap_start = 0x01000000;  // Example start address
static unsigned long heap_end = 0x01000000;
static unsigned long heap_max = 0x02000000;      // Example maximum

void init_memory() {
    heap_end = heap_start;
    print_string("Memory management initialized.\n");
}

void *kmalloc(unsigned long size) {
    void *addr = (void *)heap_end;
    heap_end += size;
    if (heap_end >= heap_max) {
        print_string("kmalloc: Out of memory!\n");
        return 0;
    }
    return addr;
}
