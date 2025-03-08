#include "fs.h"
#include "memory.h"
#include "string.h"

// Array to store file metadata
static file_t files[MAX_FILES];
static int file_count = 0;

// Dummy file data storage
#define FILE_DATA_SIZE 1024
static uint8_t file_data[MAX_FILES][FILE_DATA_SIZE];

void fs_init() {
    // Initialize the file system
    file_count = 0;
}

file_t* fs_open(const char* filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            return &files[i];
        }
    }
    return NULL; // File not found
}

void fs_close(file_t* file) {
    // No action needed for in-memory file system
}

int fs_read(file_t* file, void* buffer, uint32_t size) {
    if (file == NULL || buffer == NULL) {
        return -1; // Invalid arguments
    }

    if (size > file->size) {
        size = file->size; // Adjust size to file size
    }

    memcpy(buffer, file_data[file->start_block], size);
    return size;
}

file_t* fs_create(const char* filename, const uint8_t* data, uint32_t size) {
    if (file_count >= MAX_FILES || size > FILE_DATA_SIZE) {
        return NULL; // No space for new file or data too large
    }

    file_t* file = &files[file_count];
    strcpy(file->name, filename);
    file->size = size;
    file->start_block = file_count;

    memcpy(file_data[file_count], data, size);
    file_count++;

    return file;
}