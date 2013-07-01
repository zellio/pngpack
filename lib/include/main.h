

#ifndef __PNGPACK_H__
#define __PNGPACK_H__ 1


#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <zlib.h>

#include "memblk.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


static inline byte* pack_uint32(byte* ptr, uint32_t ui32);
static inline size_t write_memblk(FILE* fp, memblk_t* block);

memblk_t* build_file_chunk(char* filename);
int generate_packed_png(char* src, char* dst);

int main(int argc, char** argv);


#ifdef __cplusplus
};
#endif

#endif
