#include "fs.h"
#include "memory.h"
#include "string.h"
#include "video.h"

// FAT32 BPB
typedef struct {
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sector_count;
    uint8_t num_fats;
    uint32_t fat_size_32;
    uint32_t root_cluster;
} fat32_bpb_t;

typedef struct {
    char name[32];
    uint32_t size;
    uint32_t start_cluster;
} file_t;

static fat32_bpb_t bpb;

// Array to store file metadata
static file_t files[MAX_FILES];
static int file_count = 0;

// Dummy file data storage
#define FILE_DATA_SIZE 1024
static uint8_t file_data[MAX_FILES][FILE_DATA_SIZE];

void fs_init() {
    // Initialize the file system (dummy implementation)
    file_count = 0;

    // Read BPB from disk (dummy implementation)
    // In a real implementation, you would read the BPB from the disk
    bpb.bytes_per_sector = 512;
    bpb.sectors_per_cluster = 8;
    bpb.reserved_sector_count = 32;
    bpb.num_fats = 2;
    bpb.fat_size_32 = 1024;
    bpb.root_cluster = 2;
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
    // Dummy implementation (no action needed)
}

int fs_read(file_t* file, void* buffer, uint32_t size) {
    if (file == NULL || buffer == NULL) {
        return -1; // Invalid arguments
    }

    if (size > file->size) {
        size = file->size; // Adjust size to file size
    }

    memcpy(buffer, file_data[file->start_cluster], size);
    return size;
}

file_t* fs_create(const char* filename, const uint8_t* data, uint32_t size) {
    if (file_count >= MAX_FILES || size > FILE_DATA_SIZE) {
        return NULL; // No space for new file or data too large
    }

    file_t* file = &files[file_count];
    strcpy(file->name, filename);
    file->size = size;
    file->start_cluster = file_count;

    memcpy(file_data[file_count], data, size);
    file_count++;

    return file;
}