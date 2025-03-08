#ifndef FS_H
#define FS_H

#include <stdint.h>

#define MAX_FILES 128
#define FILE_DATA_SIZE 1024

typedef struct {
    char name[32];
    uint32_t size;
    uint32_t start_block;
    uint8_t data[FILE_DATA_SIZE];
} file_t;

void fs_init();
file_t* fs_open(const char* filename);
void fs_close(file_t* file);
int fs_read(file_t* file, void* buffer, uint32_t size);
file_t* fs_create(const char* filename, const uint8_t* data, uint32_t size);

#endif // FS_H