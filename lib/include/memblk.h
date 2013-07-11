

#ifndef __ZHE_PNGPACK_MEMBLK_H__
#define __ZHE_PNGPACK_MEMBLK_H__ 1


#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


#define X64_TO_I(x) ((('A'<=(x))&&((x)<='Z'))?((x)-'A'):          \
                     ((('a'<=(x))&&((x)<='z'))?((x)-'a'+26):      \
                      ((('0'<=(x))&&((x)<='9'))?((x)-'0'+52):     \
                       (((x)=='+')?(62):(((x)=='/')?(63):(0))))))


typedef uint8_t byte;

typedef struct memblk memblk_t;
struct memblk {
    size_t size;
    byte* data;
};


memblk_t* memblk_create(size_t size);
int memblk_destroy(memblk_t* memblk);

memblk_t* memblk_x64_unpack(char* data);
char* memblk_x64_digest(memblk_t* in);

size_t memblk_fread(memblk_t* block, size_t size, FILE* fp);
size_t memblk_fwrite(memblk_t* block, size_t size, FILE* fp);

size_t memblk_contents_x64_pack(memblk_t* block);
size_t memblk_contents_x64_unpack(memblk_t* block);


size_t memblk_contents_deflate(memblk_t* block);
size_t memblk_contents_inflate(memblk_t* block);


#ifdef __cplusplus
};
#endif

#endif
