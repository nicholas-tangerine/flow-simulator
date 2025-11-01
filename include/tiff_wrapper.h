#ifndef TIFF_WRAPPER_H
#define TIFF_WRAPPER_H

#include <stdlib.h>

unsigned char *uchar_convert(int *intensity_buffer, uint32_t len_buffer);

void write_bw(unsigned char *intensity_buffer, uint32_t width, uint32_t height, char *output_file);

#endif
