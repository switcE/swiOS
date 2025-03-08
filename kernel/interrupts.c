#include "interrupts.h"
#include "video.h"

struct idt_entry {
    unsigned short base_low;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

#define IDT_SIZE 256
struct idt_entry idt[IDT_SIZE];
struct idt_ptr idtp;

// Declaration of assembly routine to load the IDT
extern void idt_load(unsigned int);

// Default interrupt handler
void default_interrupt_handler() {
    print_string("Interrupt occurred!\n");
}

void set_idt_entry(int i, unsigned int base, unsigned short sel, unsigned char flags) {
    idt[i].base_low = base & 0xFFFF;
    idt[i].sel = sel;
    idt[i].always0 = 0;
    idt[i].flags = flags;
    idt[i].base_high = (base >> 16) & 0xFFFF;
}

void init_interrupts() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idtp.base = (unsigned int)&idt;

    for (int i = 0; i < IDT_SIZE; i++) {
        set_idt_entry(i, (unsigned int)default_interrupt_handler, 0x08, 0x8E);
    }
    
    idt_load((unsigned int)&idtp);
    print_string("Interrupts initialized.\n");
}
