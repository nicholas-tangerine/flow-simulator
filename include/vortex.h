#ifndef VORTEX_H
#define VORTEX_H

#include "vectors.h"

/**
 * Returns a vector field representing the velocity at each point given by
 * Burgers vortex
 *
 * REFERENCE: https://link.springer.com/book/10.1007/978-3-540-29028-5
 *
 * @param alpha         strain rate
 * @param gamma         circulatin
 * @param nu            kinematic viscosity
 *
 * @param vector field of burgers vortex
 */
vector_field_t *burgers_vortex(double alpha, double gamma, double nu, uint32_t
        width, uint32_t height, uint32_t center_x, uint32_t center_y);

/**
 * idk wikipedia made it its own function
 */
double g(double alpha, double nu, double r);

#endif
