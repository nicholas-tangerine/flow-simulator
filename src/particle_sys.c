#include <stdlib.h>

#include "particle_sys.h"

#include "math_helper.h"

particle_t **particle_system_random_init(uint32_t num_particles, double max_x, double max_y) {
    particle_t **particle_sys = calloc((size_t) num_particles, sizeof(particle_t *));

    for (int i = 0; i < (int) num_particles; i++) {
        particle_sys[i] = particle_init_random(max_x, max_y);
    }

    return particle_sys;
}

void particle_sys_advect(vector_field_t *velo_field, particle_t **particle_sys, uint32_t num_particles, double dt) {
    for (int i = 0; i < (int) num_particles; i++) {
        particle_t *curr_particle = particle_sys[i];

        int pos_x = (int) curr_particle->x;
        int pos_y = (int) curr_particle->y;

        uint32_t velo_field_width = velo_field->field_width;
        uint32_t velo_field_height = velo_field->field_height;
        int velo_field_index = get_index(velo_field_width, velo_field_height, pos_x, pos_y);

        double v_x = velo_field->x_component[velo_field_index];
        double v_y = velo_field->y_component[velo_field_index];

        curr_particle->x += v_x * dt;
        curr_particle->y += v_y * dt;
    }
}

void particle_sys_free(particle_t **particle_sys, uint32_t num_particles) {
    for (int i = 0; i < (int) num_particles; i++) {
        particle_free(particle_sys[i]);
    }

    free(particle_sys);
}
