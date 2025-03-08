#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#define IDT_SIZE 256

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(int n, uint32_t handler);
void idt_install();

#endif // INTERRUPTS_H