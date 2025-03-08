#include "kernel.h"
#include "video.h"
#include "keyboard.h"
#include "interrupts.h"

void kernel_main() {
    clear_screen();
    print("Welcome to swiOS Kernel\n");

    idt_install();
    keyboard_init();

    while (1) {
        // Kernel main loop
    }
}

void kernel_panic(const char* message) {
    print("Kernel Panic: ");
    print(message);
    while (1) {
        // Halt the system
    }
}