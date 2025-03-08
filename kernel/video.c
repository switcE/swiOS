#include "video.h"
#include "memory.h"

static uint16_t* video_memory = (uint16_t*)VIDEO_ADDRESS;
static int cursor_row = 0;
static int cursor_col = 0;

static void move_cursor() {
    uint16_t cursor_location = cursor_row * MAX_COLS + cursor_col;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, cursor_location >> 8);
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, cursor_location);
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            video_memory[row * MAX_COLS + col] = (WHITE_ON_BLACK << 8) | ' ';
        }
    }
    cursor_row = 0;
    cursor_col = 0;
    move_cursor();
}

void print_char(char character, int col, int row, char attribute_byte) {
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    if (col >= 0 && row >= 0) {
        cursor_row = row;
        cursor_col = col;
    }

    uint16_t attribute = attribute_byte << 8;
    uint16_t* location = video_memory + (cursor_row * MAX_COLS + cursor_col);
    *location = attribute | character;

    cursor_col++;
    if (cursor_col >= MAX_COLS) {
        cursor_col = 0;
        cursor_row++;
    }

    move_cursor();
}

void print_at(const char* message, int col, int row) {
    if (col >= 0 && row >= 0) {
        cursor_row = row;
        cursor_col = col;
    }

    while (*message) {
        print_char(*message++, cursor_col, cursor_row, WHITE_ON_BLACK);
    }
}

void print(const char* message) {
    print_at(message, cursor_col, cursor_row);
}

void set_cursor(int col, int row) {
    cursor_col = col;
    cursor_row = row;
    move_cursor();
}