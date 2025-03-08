; idt_load.asm - 64-bit assembly routine to load the IDT
global idt_load
section .text
idt_load:
    lidt [rdi]    ; rdi holds pointer to the idt_ptr structure
    ret
