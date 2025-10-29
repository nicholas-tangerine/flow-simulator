#ifndef PARTICLE_SYS_H
#define PARTICLE_SYS_H

#include "vectors.h"
#include "particle.h"

particle_t **particle_system_random_init(uint32_t num_particles, double max_x, double max_y);

void particle_sys_advect(vector_field_t *velo_field, particle_t **particle_sys, uint32_t num_particles, double dt);

void particle_sys_free(particle_t **particle_sys, uint32_t num_particles);

#endif
