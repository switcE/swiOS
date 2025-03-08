#ifndef FS_H
#define FS_H

typedef struct fat32_directory_entry fat32_directory_entry;

void init_fs();
fat32_directory_entry *read_directory_entry(unsigned int cluster, unsigned int index);
void read_file_data(unsigned int cluster, unsigned int offset, unsigned char *buffer, unsigned int size);

#endif
