#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <stdint.h>

#include "vectors.h"

void write_intensity_buffer_to_ppm(double *intensity_buffer, uint32_t width, uint32_t height, char *output_file);

/**
 * Creates a matrix with 1 where a particle was detected, and 0 where no particles have been detected. Iterates forward `steps` times with time step `dt`
 *
 * @param vectors               vector_field_t containing vectors with x and y components
 * @param particle_per_row
 * @param particle_per_col
 * @param steps
 * @param dt
 *
 * @return  int matrix with 1s where particles were detected (streamlines) and 0 where always empty
 */
int *draw_streamlines_to_buffer(vector_field_t *vectors, uint32_t particle_per_row, uint32_t particle_per_col, uint32_t steps, double dt);

/**
 * Iterates over `streamlines` and writes 255 where a streamline exists. Otherwise writes 0
 *
 * @param vectors               vector_field_t containing width and height and area dimensions
 * @param streamlines           streamlines to draw to ppm file
 * @param output_file           name of file to draw to
 */
void write_streamlines_to_ppm(vector_field_t *vectors, int *streamlines, char *output_file);

#endif
