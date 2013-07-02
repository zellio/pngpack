

#ifndef __PNGPACK_PACK_H__
#define __PNGPACK_PACK_H__ 1


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

memblk_t* build_file_chunk(char* filename);




#ifdef __cplusplus
};
#endif

#endif
