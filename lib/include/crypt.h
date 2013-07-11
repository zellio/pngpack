

#ifndef __ZHE_PNGPACK_CRYPT_H__
#define __ZHE_PNGPACK_CRYPT_H__ 1


#include "memblk.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif



byte* crypt_load_key(char* filename);

size_t
crypt_initialize_ectx(byte* key_data, size_t key_length, EVP_CIPHER_CTX* ctx);

size_t
crypt_initialize_dctx(byte* key_data, size_t key_length, EVP_CIPHER_CTX* ctx);



#ifdef __cplusplus
};
#endif

#endif
