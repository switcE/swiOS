#include "interrupts.h"
#include "memory.h"
#include "keyboard.h"

extern void idt_load(uint32_t);

static idt_entry_t idt[IDT_SIZE];
static idt_ptr_t idt_ptr;

void idt_set_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x08; // Kernel code segment
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E; // Interrupt gate
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_install() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    memset(&idt, 0, sizeof(idt));

    // Set up the IDT entries here (e.g., for keyboard interrupt)
    idt_set_gate(33, (uint32_t)keyboard_handler); // IRQ1 is mapped to IDT entry 33

    idt_load((uint32_t)&idt_ptr);
}