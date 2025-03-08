#include "fs.h"
#include "video.h"
#include "memory.h"
#include "lib.h"

#define SECTOR_SIZE 512

// --- Simulated Disk I/O ---
// In a real OS, disk access would use hardware or UEFI protocols.
// Here we simulate a disk image at a fixed memory address.
unsigned char *disk_image = (unsigned char *)0x00800000;
unsigned long disk_image_size = 10 * 1024 * 1024; // 10 MB

// Read one sector from the simulated disk image
static void read_sector(unsigned int sector, void *buffer) {
    unsigned long offset = sector * SECTOR_SIZE;
    if (offset + SECTOR_SIZE > disk_image_size) {
        print_string("read_sector: Out of bounds!\n");
        return;
    }
    kmemcpy(buffer, disk_image + offset, SECTOR_SIZE);
}

// --- FAT32 Structures ---
typedef struct {
    unsigned char jump[3];
    unsigned char oem_id[8];
    unsigned short bytes_per_sector;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char num_fats;
    unsigned short root_entry_count;
    unsigned short total_sectors_16;
    unsigned char media_descriptor;
    unsigned short fat_size_16;
    unsigned short sectors_per_track;
    unsigned short num_heads;
    unsigned int hidden_sectors;
    unsigned int total_sectors_32;
    unsigned int fat_size_32;
    unsigned short ext_flags;
    unsigned short fs_version;
    unsigned int root_cluster;
    unsigned short fs_info_sector;
    unsigned short backup_boot_sector;
    unsigned char reserved[12];
    unsigned char drive_number;
    unsigned char reserved2;
    unsigned char boot_signature;
    unsigned int volume_id;
    unsigned char volume_label[11];
    unsigned char fs_type[8];
} __attribute__((packed)) fat32_boot_sector;

typedef struct {
    unsigned char name[11];
    unsigned char attr;
    unsigned char reserved;
    unsigned char creation_time_tenth;
    unsigned short creation_time;
    unsigned short creation_date;
    unsigned short last_access_date;
    unsigned short first_cluster_hi;
    unsigned short modified_time;
    unsigned short modified_date;
    unsigned short first_cluster_lo;
    unsigned int file_size;
} __attribute__((packed)) fat32_directory_entry;

typedef struct {
    fat32_boot_sector *boot_sector;
    unsigned char *fat_table;
    unsigned int root_cluster;
} fat32_fs;

static fat32_fs fs;

void init_fs() {
    // Read boot sector
    fs.boot_sector = (fat32_boot_sector *)kmalloc(sizeof(fat32_boot_sector));
    read_sector(0, fs.boot_sector);
    fs.root_cluster = fs.boot_sector->root_cluster;

    // Read FAT table (simplified: one sector)
    fs.fat_table = (unsigned char *)kmalloc(SECTOR_SIZE);
    unsigned int fat_start_sector = fs.boot_sector->reserved_sectors;
    read_sector(fat_start_sector, fs.fat_table);

    print_string("FAT32 Filesystem initialized.\n");

    // List first 10 directory entries in the root (simplified)
    for (unsigned int i = 0; i < 10; i++) {
        fat32_directory_entry *entry = (fat32_directory_entry *)kmalloc(sizeof(fat32_directory_entry));
        read_sector(fs.root_cluster + i, entry);
        if (entry->name[0] == 0)
            break;
        if (entry->name[0] != 0xE5) { // Not deleted
            print_string("File: ");
            print_string((char *)entry->name);
            print_string("\n");
        }
    }
}

fat32_directory_entry *read_directory_entry(unsigned int cluster, unsigned int index) {
    fat32_directory_entry *entry = (fat32_directory_entry *)kmalloc(sizeof(fat32_directory_entry));
    read_sector(cluster + index, entry);
    return entry;
}

void read_file_data(unsigned int cluster, unsigned int offset, unsigned char *buffer, unsigned int size) {
    // Simplified: read one sector from the disk image.
    read_sector(cluster, buffer);
}
