#include "shell.h"
#include "video.h"
#include "keyboard.h"
#include "string.h"

void shell_init() {
    clear_screen();
    print("Welcome to swiOS Shell\n");
}

void shell_run() {
    char buffer[256];
    while (1) {
        print("> ");
        int index = 0;
        char c;
        while ((c = keyboard_read_scan_code()) != '\n') {
            if (c != 0) {
                buffer[index++] = c;
                print_char(c, -1, -1, WHITE_ON_BLACK);
            }
        }
        buffer[index] = '\0';
        print("\n");
        process_command(buffer);
    }
}

void process_command(const char* command) {
    if (strcmp(command, "help") == 0) {
        print("Available commands:\n");
        print("help - Show this help message\n");
        print("clear - Clear the screen\n");
        // Add more commands here
    } else if (strcmp(command, "clear") == 0) {
        clear_screen();
    } else {
        print("Unknown command: ");
        print(command);
        print("\n");
    }
}