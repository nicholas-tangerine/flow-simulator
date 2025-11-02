#include "tiffio.h"

#include "tiff_wrapper.h"
#include "particle_sys.h"

unsigned char *uchar_convert(int *intensity_buffer, uint32_t len_buffer) {
    unsigned char *out = calloc(len_buffer, sizeof(char));
    for (int i = 0; i < (int) len_buffer; i++) {
        out[i] = (unsigned char) intensity_buffer[i];
    }

    return out;
}

void write_bw(unsigned char *intensity_buffer, uint32_t width, uint32_t height, char *output_file) {
    TIFF *tif = TIFFOpen(output_file, "w");

    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);        //  8 bit smaples
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);      //  1 sample per pixel
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, 1);          //  indicate black and white

    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);

    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);


    for (int y = 0; y < (int) height; y++) {
        int index = y * (int) width;
        TIFFWriteScanline(tif, intensity_buffer + index, (uint32_t) y, 0);
    }

    TIFFClose(tif);

    return;
}
