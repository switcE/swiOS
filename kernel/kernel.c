#include "kernel.h"
#include "video.h"
#include "memory.h"
#include "interrupts.h"
#include "fs.h"
#include "keyboard.h"

void kernel_main() {
    init_video();
    print_string("Welcome to My OS Kernel!\n");

    init_memory();
    init_interrupts();
    init_fs();
    init_keyboard();

    // Main loop (placeholder for task scheduling and system calls)
    while (1) {
        // You could poll the keyboard or handle other tasks here.
    }
}
