#ifndef PARTICLE_SYS_RENDER_H
#define PARTICLE_SYS_RENDER_H

#include <stdlib.h>

#include "particle_sys.h"

int *particle_sys_density_map(particle_sys_t *sys, uint32_t width, uint32_t height);

void particle_sys_density_normalize(int *buffer, uint32_t buffer_size, int max_intensity);

#endif
