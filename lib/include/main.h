

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
#include "pack.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


int write_packed_png(char* src, char* dst);

int main(int argc, char** argv);


#ifdef __cplusplus
};
#endif

#endif
