#include <math.h>
#include <stdio.h>

#include "particle_sys_render.h"

#include "math_helper.h"

int *particle_sys_density_map(particle_sys_t *sys, uint32_t width, uint32_t height) {
    int *buffer = calloc(width * height, sizeof(int));

    for (int i = 0; i < (int) sys->num_particles; i++) {
        particle_t particle = sys->particles[i];

        int x = (int) floor(particle.x);
        int y = (int) floor(particle.y);

        int index = get_index(width, height, x, y);

        buffer[index]++;
    }

    return buffer;
}

void particle_sys_density_normalize(int *buffer, uint32_t buffer_size, int max_intensity) {
    int max_buffer = 0;

    for (int i = 0; i < (int) buffer_size; i++) {
        int curr = buffer[i];
        max_buffer = curr > max_buffer ? curr : max_buffer;
    }

    printf("max buffer: %d\n", max_buffer);

    double scaler = (double) max_intensity / (double) max_buffer;

    for (int i = 0; i < (int) buffer_size; i++) {
        buffer[i] = (int) ((double) buffer[i] * scaler);
    }
}
