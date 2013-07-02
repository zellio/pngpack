

#include "pack.h"



static inline byte* pack_uint32(byte* ptr, uint32_t ui32) {
    *ptr++ = (ui32 >> 24) & 0xff;
    *ptr++ = (ui32 >> 16) & 0xff;
    *ptr++ = (ui32 >> 8) & 0xff;
    *ptr++ = (ui32) & 0xff;
    return ptr;
}

memblk_t* build_file_chunk(char* filename) {
    struct stat st;
    stat(filename, &st);
    size_t size = st.st_size;

    FILE* fp = fopen(filename, "rb");
    byte* fdata = calloc(size, sizeof(uint8_t));
    fflush(stdin);
    fread(fdata, sizeof(uint8_t), size, fp);
    fclose(fp);

    memblk_t* container = memblk_create(0);
    container->data = fdata;
    container->size = size;

    byte* f64_data = (byte*)memblk_x64_digest(container);
    size_t f64_size = (size + 2) / 3 * 4;

    free(fdata);

    container->data = calloc(f64_size + 12, sizeof(byte));
    container->size = f64_size + 12;

    byte* data = container->data;

    data = pack_uint32(data, f64_size);

    byte* crc_start = data;

    data = pack_uint32(data, 0x69545874);

    memcpy(data, f64_data, f64_size);
    data += f64_size;

    uint64_t crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, crc_start, f64_size + 4);

    pack_uint32(data, crc);

    return container;
}
