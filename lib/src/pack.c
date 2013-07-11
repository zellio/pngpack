

#include "pack.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <zlib.h>


byte* pack_uint32(byte* ptr, uint32_t ui32) {
    *ptr++ = (ui32 >> 24) & 0xff;
    *ptr++ = (ui32 >> 16) & 0xff;
    *ptr++ = (ui32 >> 8) & 0xff;
    *ptr++ = (ui32) & 0xff;
    return ptr;
}

byte* unpack_uint32(byte* ptr, uint32_t* ui32_ptr) {
    *ui32_ptr += ((*ptr++) << 24);
    *ui32_ptr += ((*ptr++) << 16);
    *ui32_ptr += ((*ptr++) << 8);
    *ui32_ptr += ((*ptr++) << 0);
    return ptr;
}


memblk_t* pack_file(char* filename) {
    struct stat st;
    stat(filename, &st);
    size_t size = st.st_size;
    FILE* fp = fopen(filename, "rb");

    memblk_t* fdata = memblk_create(size);
    memblk_fread(fdata, size, fp);
    memblk_contents_deflate(fdata);

    size_t fdata_size = fdata->size;
    size_t container_size = fdata_size + 20;

    memblk_t* container = memblk_create(container_size);

    byte* fdata_data = fdata->data;
    byte* container_data = container->data;

    container_data = pack_uint32(container_data, fdata_size + 8);
    byte* crc_start = container_data;

    container_data = pack_uint32(container_data, 0x69545874);
    container_data = pack_uint32(container_data, 0x436f6d6d);
    container_data = pack_uint32(container_data, 0x656e7400);

    memcpy(container_data, fdata_data, fdata_size);
    container_data += fdata_size;

    uint64_t crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, crc_start, fdata_size + 12);

    pack_uint32(container_data, crc);

    memblk_destroy(fdata);
    fclose(fp);

    return container;
}

memblk_t* unpack_file(char* filename) {
    FILE* fp = fopen(filename, "rb");
    fseek(fp, 55L, SEEK_SET);

    byte* size_blob = calloc(4, sizeof(byte));
    fread(size_blob, sizeof(byte), 4, fp);

    uint32_t fd64_size;
    unpack_uint32(size_blob, &fd64_size);
    free(size_blob);

    memblk_t* block = memblk_create(fd64_size - 8);
    fseek(fp, 12L, SEEK_CUR);
    memblk_fread(block, fd64_size - 8, fp);

    memblk_contents_inflate(block);

    return block;
}
