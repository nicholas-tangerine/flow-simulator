#ifndef NOISE_H
#define NOISE_H

#include <stdint.h>

#include "vectors.h"

double *generate_intensity_field(uint32_t width, uint32_t height);

double generate_intensity_point(vector_field_t *perlin_field, int x_intensity_idx, int y_intensity_idx);

#endif
