#include "interrupts.h"
#include "video.h"
#include "string.h"

#define IDT_SIZE 256

// IDT entry structure
struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// IDT pointer structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// IDT
struct idt_entry idt[IDT_SIZE];
struct idt_ptr idtp;

extern void idt_load();

// Define struct regs
struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

// Function prototypes for IRQ handlers
extern "C" void irq0();
extern "C" void irq1();

// Function to set an IDT gate
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// IRQ handler function
extern "C" void irq_handler(struct regs *r) {
    // Send EOI (End of Interrupt) to PICs
    if (r->int_no >= 40) {
        // Send to slave PIC if IRQ8-15
        outb(0xA0, 0x20);
    }
    // Send to master PIC for all IRQs
    outb(0x20, 0x20);
    
    // Add IRQ handling logic here (or call appropriate handler)
}

// Initialize and install the IDT
void idt_install() {
    // Set up IDT pointer
    idtp.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idtp.base = (uint32_t)&idt;
    
    // Clear IDT
    memset(&idt, 0, sizeof(struct idt_entry) * IDT_SIZE);

    // Remap the PIC
    // Initialize command (ICW1): start initialization sequence in cascade mode
    outb(0x20, 0x11);  // Master PIC
    outb(0xA0, 0x11);  // Slave PIC
    
    // ICW2: Set vector offset
    outb(0x21, 0x20);  // Master PIC IRQs start at 32 (0x20)
    outb(0xA1, 0x28);  // Slave PIC IRQs start at 40 (0x28)
    
    // ICW3: Tell Master PIC that there is a slave at IRQ2
    outb(0x21, 0x04);  // Bit 2 is set (0000 0100)
    // ICW3: Tell Slave PIC its cascade identity
    outb(0xA1, 0x02);  // Slave PIC is at IRQ2 of master (0000 0010)
    
    // ICW4: Set mode
    outb(0x21, 0x01);  // 8086/88 mode
    outb(0xA1, 0x01);  // 8086/88 mode
    
    // Unmask all interrupts
    outb(0x21, 0x0);   // Master PIC
    outb(0xA1, 0x0);   // Slave PIC

    // Set IDT gates for IRQs
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E); // Timer interrupt
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E); // Keyboard interrupt
    
    // Set other IRQ gates here
    // For example:
    // idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E); // Cascade
    // idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E); // COM2
    // idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E); // COM1
    // idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E); // LPT2
    // idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E); // Floppy disk
    // idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E); // LPT1
    // idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E); // CMOS real-time clock
    // idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E); // Free for peripherals
    // idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E); // Free for peripherals
    // idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E); // Free for peripherals
    // idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E); // PS2 Mouse
    // idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E); // FPU
    // idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E); // Hard disk
    // idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E); // Free for peripherals
    
    // Load IDT
    idt_load();
}

// Main interrupt initialization function
void isr_install() {
    idt_install();
}

// IRQ0 handler (Timer)
extern "C" void irq0() {
    // Disable interrupts
    asm volatile ("cli");
    
    // Save registers and call C handler
    asm volatile (
        "pushal\n"           // Push all registers
        "push %ds\n"         // Save data segment
        "push %es\n"         // Save extra segment
        "push %fs\n"         // Save F segment
        "push %gs\n"         // Save G segment
        "mov $0x10, %ax\n"   // Load kernel data segment
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov %esp, %eax\n"   // Pass stack pointer to C
        "push %eax\n"
        "mov $32, %eax\n"    // Set interrupt number (IRQ0 = 32)
        "push %eax\n"
        "call irq_handler\n" // Call C handler
        "add $8, %esp\n"     // Clean up stack
        "pop %gs\n"          // Restore segments
        "pop %fs\n"
        "pop %es\n"
        "pop %ds\n"
        "popal\n"            // Restore registers
    );
    
    // Enable interrupts
    asm volatile ("sti");
    
    // Return from interrupt
    asm volatile ("iret");
}

// IRQ1 handler (Keyboard)
extern "C" void irq1() {
    // Disable interrupts
    asm volatile ("cli");
    
    // Save registers and call C handler
    asm volatile (
        "pushal\n"           // Push all registers
        "push %ds\n"         // Save data segment
        "push %es\n"         // Save extra segment
        "push %fs\n"         // Save F segment
        "push %gs\n"         // Save G segment
        "mov $0x10, %ax\n"   // Load kernel data segment
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov %esp, %eax\n"   // Pass stack pointer to C
        "push %eax\n"
        "mov $33, %eax\n"    // Set interrupt number (IRQ1 = 33)
        "push %eax\n"
        "call irq_handler\n" // Call C handler
        "add $8, %esp\n"     // Clean up stack
        "pop %gs\n"          // Restore segments
        "pop %fs\n"
        "pop %es\n"
        "pop %ds\n"
        "popal\n"            // Restore registers
    );
    
    // Enable interrupts
    asm volatile ("sti");
    
    // Return from interrupt
    asm volatile ("iret");
}