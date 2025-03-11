#include "memory.h"
#include "video.h"

#define MEMORY_SIZE 0x1000000 // 16 MB
#define PAGE_SIZE 4096

static uint8_t memory[MEMORY_SIZE];
static uint32_t free_memory = MEMORY_SIZE;

// Heap management structures
typedef struct heap_block {
    uint32_t size;
    struct heap_block* next;
} heap_block_t;

static heap_block_t* free_list = (heap_block_t*)memory;

void memory_init() {
    free_list->size = MEMORY_SIZE - sizeof(heap_block_t);
    free_list->next = NULL;
    free_memory = free_list->size;
}

void* memory_alloc(uint32_t size) {
    heap_block_t* current = free_list;
    heap_block_t* previous = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            if (current->size > size + sizeof(heap_block_t)) {
                heap_block_t* new_block = (heap_block_t*)((uint8_t*)current + sizeof(heap_block_t) + size);
                new_block->size = current->size - size - sizeof(heap_block_t);
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }

            if (previous == NULL) {
                free_list = current->next;
            } else {
                previous->next = current->next;
            }

            free_memory -= size + sizeof(heap_block_t);
            return (void*)((uint8_t*)current + sizeof(heap_block_t));
        }

        previous = current;
        current = current->next;
    }

    return NULL; // Not enough memory
}

void memory_free(void* ptr, uint32_t size) {
    heap_block_t* block = (heap_block_t*)((uint8_t*)ptr - sizeof(heap_block_t));
    block->size = size;
    block->next = free_list;
    free_list = block;
    free_memory += size + sizeof(heap_block_t);
}

uint32_t memory_get_free() {
    return free_memory;
}

void* memset(void* dest, int value, size_t len) {
    unsigned char* ptr = dest;
    while (len-- > 0) {
        *ptr++ = value;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t len) {
    const unsigned char* src_ptr = src;
    unsigned char* dest_ptr = dest;
    while (len-- > 0) {
        *dest_ptr++ = *src_ptr++;
    }
    return dest;
}

void* memmove(void* dest, const void* src, size_t len) {
    const unsigned char* src_ptr = src;
    unsigned char* dest_ptr = dest;
    if (dest_ptr < src_ptr) {
        while (len-- > 0) {
            *dest_ptr++ = *src_ptr++;
        }
    } else {
        src_ptr += len;
        dest_ptr += len;
        while (len-- > 0) {
            *--dest_ptr = *--src_ptr;
        }
    }
    return dest;
}

int memcmp(const void* ptr1, const void* ptr2, size_t len) {
    const unsigned char* p1 = ptr1;
    const unsigned char* p2 = ptr2;
    while (len-- > 0) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}