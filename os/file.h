#ifndef FILE_H
#define FILE_H

#include <stdint.h>

#define MAX_FILES 128

typedef struct {
    char name[32];
    uint32_t size;
    uint32_t start_block;
} file_t;

void file_init();
file_t* file_open(const char* filename);
void file_close(file_t* file);
int file_read(file_t* file, void* buffer, uint32_t size);

#endif // FILE_H