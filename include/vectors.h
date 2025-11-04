#ifndef VECTORS_H
#define VECTORS_H

#include <stdint.h>

typedef struct {
    double *x_component;
    double *y_component;
    uint32_t field_width;
    uint32_t field_height;
    uint32_t field_area;
} vector_field_t;

typedef struct {
    double *scalars;
    uint32_t field_width;
    uint32_t field_height;
    uint32_t field_area;
} scalar_field_t;

/**
 * Allocates memory for the vector field to be used to generate the Perlin Noise. 2d array of 2d vectors stored in `x_component` and `y_component`
 *
 * @param width             width of field (width of output image + 1)
 * @param height            height of field (height of output image + 1)
 *
 * @return  initialized vector_field_t with random values for vectors
 */
vector_field_t *vector_field_init(uint32_t width, uint32_t height);

vector_field_t *vector_field_init_random(uint32_t width, uint32_t height);

void vector_field_normalize(vector_field_t *vectors);

void vector_field_free(vector_field_t *vectors);

/**
 * Allocates memory for the scalar field to be used to store the Perlin Noise. Matrix stored in 1d array
 *
 * @param width             width of the field (width of output image + 0)
 * @param height            height of the field (height of output image + 0)
 *
 * @return  initialized scalar_field_t filled with 0's
 */
scalar_field_t *scalar_field_init(uint32_t width, uint32_t height);

scalar_field_t *scalar_field_init_random(uint32_t width, uint32_t height);

scalar_field_t *vector_magnitude_field(vector_field_t *vectors);

void scalar_field_free(scalar_field_t *scalars);

#endif
