#include "../include/stdlib.h"
#include "../include/paging.h"  // Assuming there is a paging/memory management system

extern unsigned int end;
unsigned int placement_address = (unsigned int)&end;

void *malloc(size_t size) {
    unsigned int tmp = placement_address;
    placement_address += size;
    return (void *)tmp;
}

void free(void *ptr) {
    (void)ptr;
    // Basic implementation doesn't handle freeing
}
