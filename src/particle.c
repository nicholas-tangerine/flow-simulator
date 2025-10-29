#include <stdlib.h>

#include "particle.h"
#include "vectors.h"

#include "math_helper.h"

particle_t *particle_init(double x, double y) {
    particle_t *particle = calloc(1, sizeof(particle_t));
    particle->x = x;
    particle->y = y;

    return particle;
}

particle_t *particle_init_random(double max_x, double max_y) {
    particle_t *particle = calloc(1, sizeof(particle_t));
    particle->x = rand() / RAND_MAX;
    particle->x *= max_x;
    particle->y = rand() / RAND_MAX;
    particle->y *= max_y;

    return particle;
}

void particle_free(particle_t *particle) {
    free(particle);
}
