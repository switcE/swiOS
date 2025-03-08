#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

// Screen i/o ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen();
void print_char(char character, int col, int row, char attribute_byte);
void print_at(const char* message, int col, int row);
void print(const char* message);
void set_cursor(int col, int row);

#endif // VIDEO_H