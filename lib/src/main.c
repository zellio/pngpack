

#include "main.h"


int write_packed_png(char* src, char* dst) {
    memblk_t* png_header = memblk_x64_unpack("iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAACklEQVR4nGMAAQAABQABDQottAA==");
    memblk_t* png_footer = memblk_x64_unpack("AAAAAElFTkSuQmCC");
    memblk_t* file_chunk = build_file_chunk(src);

    FILE* fp = fopen(dst, "w");

    fflush(stdout);

    memblk_write(png_header, fp);
    memblk_write(file_chunk, fp);
    memblk_write(png_footer, fp);

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

    write_packed_png(src, dst);
    return 0;
}
