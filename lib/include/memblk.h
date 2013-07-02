
#ifndef __ZHE_MATASANO_TYPE_MEMBLK_H__
#define __ZHE_MATASANO_TYPE_MEMBLK_H__ 1


#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#define UPCASE_CHAR(x) ((('a'<=(x))&&((x)<='z'))?((x)-'a'+'A'):(x))
#define DOWNCASE_CHAR(x) ((('A'<=(x))&&((x)<='Z'))?((x)-'A'+'a'):(x))
#define DOWNCASE_HEXCHAR_TO_I(x) ((('0'<=(x))&&((x)<='9'))?((x)-'0'):   \
                                  ((('a'<=(x))&&((x)<='f'))?((x)-'a'+10):0))
#define HEXCHAR_TO_I(x) (DOWNCASE_HEXCHAR_TO_I(DOWNCASE_CHAR((x))))

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

size_t memblk_write(memblk_t* block, FILE* fp);


#ifdef __cplusplus
};
#endif

#endif
