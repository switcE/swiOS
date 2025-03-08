#include "keyboard.h"
#include "video.h"
#include "interrupts.h"

static char key_buffer[256];

void keyboard_handler() {
    uint8_t status;
    char keycode;

    // Write end of interrupt (EOI)
    outb(0x20, 0x20);

    status = inb(KEYBOARD_STATUS_PORT);
    // Lowest bit of status will be set if buffer is not empty
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
        if (keycode < 0) {
            return;
        }

        // Handle the keycode (convert to ASCII and store in buffer)
        char ascii = keyboard_scan_code_to_ascii(keycode);
        if (ascii != 0) {
            // Print the character to the screen
            print_char(ascii, -1, -1, WHITE_ON_BLACK);
        }
    }
}

void keyboard_init() {
    // Register the keyboard handler
    idt_set_gate(33, (uint32_t)keyboard_handler);
}

char keyboard_read_scan_code() {
    // Read the scan code from the keyboard data port
    return inb(KEYBOARD_DATA_PORT);
}

char keyboard_scan_code_to_ascii(char scan_code) {
    // Convert scan code to ASCII (simplified for demonstration)
    static char ascii_map[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
        '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    if (scan_code > 0 && scan_code < 128) {
        return ascii_map[(int)scan_code];
    } else {
        return 0;
    }
}