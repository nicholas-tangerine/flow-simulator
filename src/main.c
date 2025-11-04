#include <stdlib.h>
#include <stdio.h>

#include "noise.h"
#include "vectors.h"
#include "vortex.h"
#include "particle.h"
#include "particle_sys.h"
#include "particle_sys_render.h"
#include "tiff_wrapper.h"
#include "debug_utils.h"

#define IMAGE_WIDTH 1800
#define IMAGE_HEIGHT (IMAGE_WIDTH / 2)

#define VORTEX_ALPHA -2e-2
#define VORTEX_GAMMA -1e4
#define VORTEX_NU -2.25e2
#define VORTEX_CENTER_X (IMAGE_WIDTH / 2)
#define VORTEX_CENTER_Y (IMAGE_HEIGHT / 2)

#define PARTICLE_SYS_NUM_PARTS 1000000
#define PARTICLE_SYS_MAX_X ((double) IMAGE_WIDTH)
#define PARTICLE_SYS_MAX_Y ((double) IMAGE_HEIGHT)
#define SIMULATE_TIME_STEPS 5

#define STREAMLINE_ITERATIONS 35
#define STREAMLINE_PARTICLES_PER_ROW 200
#define STREAMLINE_PARTICLES_PER_COL (STREAMLINE_PARTICLES_PER_ROW / 2)
#define STREAMLINE_ITERATIONS_DT 0.5

int main(void) {
    vector_field_t *burgers_vortex_field = burgers_vortex(VORTEX_ALPHA, VORTEX_GAMMA, VORTEX_NU, IMAGE_WIDTH, IMAGE_HEIGHT, VORTEX_CENTER_X, VORTEX_CENTER_Y);
    vector_field_normalize(burgers_vortex_field);

    scalar_field_t *velo_mag = vector_magnitude_field(burgers_vortex_field);
    write_intensity_buffer_to_ppm(velo_mag->scalars, velo_mag->field_width, velo_mag->field_height, "velo mag.ppm");

    /**
     * PARTICLE FLOW + I/O
     */
    particle_sys_t *sys = particle_system_random_init(PARTICLE_SYS_NUM_PARTS, PARTICLE_SYS_MAX_X, PARTICLE_SYS_MAX_Y);

    int *intensity_before_int = particle_sys_density_map(sys, IMAGE_WIDTH, IMAGE_HEIGHT);
    particle_sys_density_normalize(intensity_before_int, IMAGE_WIDTH * IMAGE_HEIGHT, 255);
    unsigned char *intensity_before_ch = uchar_convert(intensity_before_int, IMAGE_WIDTH * IMAGE_HEIGHT);
    write_bw(intensity_before_ch, IMAGE_WIDTH, IMAGE_HEIGHT, "before.tif");

    for (int i = 0; i < SIMULATE_TIME_STEPS; i++) { particle_sys_advect(burgers_vortex_field, sys, 1); }

    int *intensity_after_int = particle_sys_density_map(sys, IMAGE_WIDTH, IMAGE_HEIGHT);
    particle_sys_density_normalize(intensity_after_int, IMAGE_WIDTH * IMAGE_HEIGHT, 255);
    unsigned char *intensity_after_ch = uchar_convert(intensity_after_int, IMAGE_WIDTH * IMAGE_HEIGHT);
    write_bw(intensity_after_ch, IMAGE_WIDTH, IMAGE_HEIGHT, "after.tif");

    /**
     * FREE MEMORY
     */
    vector_field_free(burgers_vortex_field);
    scalar_field_free(velo_mag);
    particle_sys_free(sys);

    free(intensity_before_int);
    free(intensity_after_int);

    free(intensity_before_ch);
    free(intensity_after_ch);


    return 0;
}
