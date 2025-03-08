#include "video.h"

static unsigned short *video_memory = (unsigned short *)0xB8000;
static unsigned short cursor_x = 0;
static unsigned short cursor_y = 0;

void init_video() {
    unsigned short blank = 0x20 | (0x07 << 8);
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = blank;
    }
}

void print_string(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            video_memory[cursor_y * 80 + cursor_x] = (unsigned short)(str[i] | (0x07 << 8));
            cursor_x++;
        }
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_y >= 25) {
            cursor_y = 0;
        }
    }
}
