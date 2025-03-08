#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_COMMAND_PORT 0x64

#define KEYBOARD_STATUS_MASK_OUT_BUF 1
#define KEYBOARD_STATUS_MASK_IN_BUF 2

void keyboard_init();
void keyboard_handler();
char keyboard_read_scan_code();
char keyboard_scan_code_to_ascii(char scan_code);

#endif // KEYBOARD_H