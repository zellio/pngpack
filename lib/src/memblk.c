

#include "memblk.h"
#include <stdlib.h>

memblk_t* memblk_create(size_t size) {
    memblk_t* memblk = calloc(1, sizeof(memblk_t));
    memblk->size = size;
    memblk->data = calloc(1, size);
    return memblk;
}

int memblk_destroy(memblk_t* memblk) {
    free(memblk->data);
    free(memblk);
    return 0;
}

memblk_t* memblk_x64_unpack(char* x64str) {
    size_t str_len = 0;
    char* ptr = x64str;
    while (*ptr++) str_len++;

    size_t size = str_len * 3 / 4;

    if (x64str[str_len - 1] == '=') size--;
    if (x64str[str_len - 2] == '=') size--;

    memblk_t* memblk = memblk_create(size);
    byte* data = memblk->data;

    size_t i = 0;
    while (i < size) {
        uint32_t s1 = X64_TO_I(*x64str); x64str++;
        uint32_t s2 = X64_TO_I(*x64str); x64str++;
        uint32_t s3 = X64_TO_I(*x64str); x64str++;
        uint32_t s4 = X64_TO_I(*x64str); x64str++;
        uint32_t t = (s1 << 18) + (s2 << 12) + (s3 << 6) + s4;

        if (i < size) data[i++] = (t >> 16) & 0xFF;
        if (i < size) data[i++] = (t >> 8) & 0xFF;
        if (i < size) data[i++] = t & 0xFF;
    }

    return memblk;
}

static char x64_digest_encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't', 'u', 'v','w', 'x', 'y', 'z', '0', '1', '2', '3','4', '5', '6', '7', '8', '9', '+', '/'};

char* memblk_x64_digest(memblk_t* in) {
    size_t size = in->size;
    size_t target_size = (size + 2) / 3 * 4;

    char* out = calloc(1, target_size);
    char* ptr = out;

    size_t i = 0;
    while (i < size) {
        uint32_t o1 = i < size ? in->data[i++] : 0,
                 o2 = i < size ? in->data[i++] : 0,
                 o3 = i < size ? in->data[i++] : 0,
                 triple = (o1 << 0x10) + (o2 << 0x08) + o3;

        for (int k = 3; k >= 0; k--)
            *ptr++ = x64_digest_encoding_table[(triple >> k * 6) & 0x3F];
    }

    switch (size % 3) {
    case 1: *ptr-- = '=';
    case 2: *ptr-- = '='; break;
    }

    return out;
}


size_t memblk_write(memblk_t* block, FILE* fp) {
    if (block == NULL)
        return 1;

    return fwrite(block->data, sizeof(uint8_t), block->size, fp);
}
