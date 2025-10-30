#include <stdlib.h>
#include <stdio.h>

#include "noise.h"
#include "vectors.h"
#include "vortex.h"
#include "particle.h"
#include "particle_sys.h"
#include "debug_utils.h"

#define IMAGE_WIDTH 1800
#define IMAGE_HEIGHT (IMAGE_WIDTH / 2)

#define VORTEX_ALPHA -2e-2
#define VORTEX_GAMMA -1e4
#define VORTEX_NU -2.25e2
#define VORTEX_CENTER_X (IMAGE_WIDTH / 2)
#define VORTEX_CENTER_Y (IMAGE_HEIGHT / 2)

#define PARTICLE_SYS_NUM_PARTS 4000000
#define PARTICLE_SYS_MAX_X ((double) IMAGE_WIDTH)
#define PARTICLE_SYS_MAX_Y ((double) IMAGE_HEIGHT)
#define SIMULATE_DT 5.0

#define STREAMLINES_PARTICLES_PER_ROW 100
#define STREAMLINES_PARTICLES_PER_COL (STREAMLINES_PARTICLES_PER_ROW / 2)
#define STREAMLINES_ITERATIONS 1000
#define STREAMLINES_DT 3.0

int main(void) {
    vector_field_t *burgers_vortex_field = burgers_vortex(VORTEX_ALPHA, VORTEX_GAMMA, VORTEX_NU, IMAGE_WIDTH, IMAGE_HEIGHT, VORTEX_CENTER_X, VORTEX_CENTER_Y);
    vector_field_normalize(burgers_vortex_field);

    particle_sys_t *sys = particle_system_random_init(PARTICLE_SYS_NUM_PARTS, PARTICLE_SYS_MAX_X, PARTICLE_SYS_MAX_Y);

    /**
     * FREE MEMORY
     */
    vector_field_free(burgers_vortex_field);
    particle_sys_free(sys);

    return 0;
}
