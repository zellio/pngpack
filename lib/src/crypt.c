

#include "crypt.h"

#include <sys/stat.h>



byte* crypt_load_key(char* filename) {
    if (filename == NULL)
        filename = "pngpack.key";

    struct stat st;
    stat(filename, &st);
    size_t size = st.st_size;
    FILE* fp = fopen(filename, "rb");

    memblk_t* block = memblk_create(size);
    memblk_fread(block, size, fp);

    byte* key_data = block->data;
    free(block);

    return key_data;
}

size_t
crypt_initialize_ectx(byte* key_data, size_t key_length, EVP_CIPHER_CTX* ctx) {
    byte key[32], iv[32];
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, key_data, key_length,
                   10, key, iv);
    EVP_CIPHER_CTX_init(ctx);
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    return 0;
}

size_t
crypt_initialize_dctx(byte* key_data, size_t key_length, EVP_CIPHER_CTX* ctx) {
    byte key[32], iv[32];
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, key_data, key_length,
                   10, key, iv);
    EVP_CIPHER_CTX_init(ctx);
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    return 0;
}
