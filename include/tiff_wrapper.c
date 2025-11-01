#ifndef TIFF_WRAPPER_H
#define TIFF_WRAPPER_H

typedef struct {
    int *intensity_buffer;
    uint32_t image_width;
    uint32_t image_height;
} tiff_img_t;

void write_bw(tiff_img_t *img, char *output_file);

#endif
