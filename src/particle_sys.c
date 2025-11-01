#include <stdlib.h>

#include "particle.h"
#include "particle_sys.h"

#include "math_helper.h"

particle_sys_t *particle_system_random_init(uint32_t num_particles, double max_x, double max_y) {
    particle_sys_t *particle_sys = calloc(1, sizeof(particle_sys_t));
    particle_sys->particles = calloc((size_t) num_particles, sizeof(particle_t));

    for (int i = 0; i < (int) num_particles; i++) {
        particle_sys->particles[i] = particle_init_random(max_x, max_y);
    }
    particle_sys->num_particles = num_particles;

    return particle_sys;
}

void particle_sys_advect(vector_field_t *velo_field, particle_sys_t *particle_sys, double dt) {
    particle_t *particles = particle_sys->particles;

    uint32_t velo_field_width = velo_field->field_width;
    uint32_t velo_field_height = velo_field->field_height;

    for (int i = 0; i < (int) particle_sys->num_particles; i++) {
        particle_t *curr_particle = &particles[i];

        int pos_x = (int) curr_particle->x;
        int pos_y = (int) curr_particle->y;

        if (pos_x < 0 || pos_x >= (int) velo_field_width) continue;
        if (pos_y < 0 || pos_y >= (int) velo_field_height) continue;

        int velo_field_index = get_index(velo_field_width, velo_field_height, pos_x, pos_y);

        double v_x = velo_field->x_component[velo_field_index];
        double v_y = velo_field->y_component[velo_field_index];

        curr_particle->x += v_x * dt;
        curr_particle->y += v_y * dt;
    }
}

void particle_sys_free(particle_sys_t *particle_sys) {
    particle_t *particles = particle_sys->particles;

    free(particles);
    free(particle_sys);
}
