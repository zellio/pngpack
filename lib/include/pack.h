

#ifndef __PNGPACK_PACK_H__
#define __PNGPACK_PACK_H__ 1


#include <stddef.h>
#include <stdint.h>

#include "memblk.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


byte* pack_uint32(byte* ptr, uint32_t ui32);
byte* unpack_uint32(byte* ptr, uint32_t* ui32_ptr);

memblk_t* pack_file(char* filename);
memblk_t* unpack_file(char* filename);


#ifdef __cplusplus
};
#endif

#endif
