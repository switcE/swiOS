#ifndef FS_H
#define FS_H

#include <stdint.h>

#define MAX_FILES 128
#define FILE_DATA_SIZE 1024

// FAT32 specific constants
#define FAT32_SIGNATURE 0xAA55
#define FAT32_EOC 0x0FFFFFF8

// FAT32 BPB (BIOS Parameter Block) structure
typedef struct {
    uint8_t jmp_boot[3];
    char oem_name[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sector_count;
    uint8_t num_fats;
    uint16_t root_entry_count;
    uint16_t total_sectors_16;
    uint8_t media;
    uint16_t fat_size_16;
    uint16_t sectors_per_track;
    uint16_t num_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    uint32_t fat_size_32;
    uint16_t ext_flags;
    uint16_t fs_version;
    uint32_t root_cluster;
    uint16_t fs_info;
    uint16_t backup_boot_sector;
    uint8_t reserved[12];
    uint8_t drive_number;
    uint8_t reserved1;
    uint8_t boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char fs_type[8];
} __attribute__((packed)) fat32_bpb_t;

// FAT32 Directory Entry structure
typedef struct {
    char name[11];
    uint8_t attr;
    uint8_t nt_res;
    uint8_t crt_time_tenth;
    uint16_t crt_time;
    uint16_t crt_date;
    uint16_t lst_acc_date;
    uint16_t fst_clust_hi;
    uint16_t wrt_time;
    uint16_t wrt_date;
    uint16_t fst_clust_lo;
    uint32_t file_size;
} __attribute__((packed)) fat32_dir_entry_t;

// File structure
typedef struct {
    char name[32];
    uint32_t size;
    uint32_t start_cluster;
    uint8_t data[FILE_DATA_SIZE];
} file_t;

void fs_init();
file_t* fs_open(const char* filename);
void fs_close(file_t* file);
int fs_read(file_t* file, void* buffer, uint32_t size);
file_t* fs_create(const char* filename, const uint8_t* data, uint32_t size);

#endif // FS_H