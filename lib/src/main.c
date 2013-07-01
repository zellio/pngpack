

#include "main.h"


static inline byte* pack_uint32(byte* ptr, uint32_t ui32) {
    *ptr++ = (ui32 >> 24) & 0xff;
    *ptr++ = (ui32 >> 16) & 0xff;
    *ptr++ = (ui32 >> 8) & 0xff;
    *ptr++ = (ui32) & 0xff;
    return ptr;
}

static inline size_t write_memblk(FILE* fp, memblk_t* block) {
    return fwrite(block->data, sizeof(uint8_t), block->size, fp);
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


int generate_packed_png(char* src, char* dst) {
    memblk_t* png_header = memblk_x64_unpack("iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAY""AAAAfFcSJAAAACklEQVR4nGMAAQAABQABDQottAA==");
    memblk_t* png_footer = memblk_x64_unpack("AAAAAElFTkSuQmCC");

    memblk_t* file_chunk = build_file_chunk(src);

    FILE* fp = fopen(dst, "w");

    fflush(stdout);

    write_memblk(fp, png_header);
    write_memblk(fp, file_chunk);
    write_memblk(fp, png_footer);

    fflush(stdout);

    memblk_destroy(png_header);
    memblk_destroy(file_chunk);
    memblk_destroy(png_footer);

    fclose(fp);

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: pngpack src dst\r\n");
        exit(1);
    }

    char* src = argv[1];
    char* dst = argv[2];

    generate_packed_png(src, dst);
    return 0;
}
