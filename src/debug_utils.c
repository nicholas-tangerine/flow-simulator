#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "math_helper.h"
#include "debug_utils.h"
#include "particle.h"
#include "particle_sys.h"

/**
 * INTENSITY BUFFERS
 */
void write_intensity_buffer_to_ppm(double *intensity_buffer, uint32_t width, uint32_t height, char *output_file) {
    if (strcmp(output_file, "") == 0) output_file = "output.ppm";

    double *buffer = intensity_buffer;

    FILE *fp = fopen(output_file, "wb");
    if (fp == NULL) {
        fprintf(stderr, "DEBUG: error opening file\n");
        return;
    }

    fprintf(fp, "P5\n%d %d\n%d\n", width , height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width ; x++) {
            uint32_t index = y * width + x;
            double buffer_val = buffer[index];

            unsigned char intensity = (unsigned char) (buffer_val * 255.0);

            fputc(intensity, fp);
        }
    }

    fclose(fp);
    fp = NULL;

    return;
}

/**
 * STREAMLINES
 */
int *draw_streamlines_to_buffer(vector_field_t *vectors, uint32_t particle_per_row, uint32_t particle_per_col, uint32_t steps, double dt) {
    uint32_t particles_count = particle_per_row * particle_per_col;

    uint32_t width = vectors->field_width;
    uint32_t height = vectors->field_height;
    uint32_t area = vectors->field_area;

    double *x_component = vectors->x_component;
    double *y_component = vectors->y_component;

    int *buffer = calloc(area, sizeof(int));            //      all values are 0 rn

    particle_t *particles = calloc(particle_per_row * particle_per_col, sizeof(particle_t));
    uint32_t particles_index = 0;

    uint32_t x_step = width / particle_per_row;
    uint32_t y_step = height / particle_per_col;

    for (uint32_t x = 0; x < particle_per_row; x++) {
        for (uint32_t y = 0; y < particle_per_col; y++) {
            particles[particles_index] = particle_init(x_step * x, y_step * y);
            buffer[get_index(width, height, (int) x_step * (int) x, (int) y_step * (int) y)] = 1;
            particles_index++;
        }
    }

    for (uint32_t a = 0; a < steps; a++) {
        for (uint32_t i = 0; i < particles_count; i++) {
            particle_t *particle = &particles[i];

            int x = (int) floor(particle->x);
            int y = (int) floor(particle->y);

            if (x < 0 || y < 0 || x >= (int) width || y >= (int) height) continue;

            int buffer_index = get_index(width, height, x, y);

            particle->x += x_component[buffer_index] * dt;
            particle->y += y_component[buffer_index] * dt;

            buffer[buffer_index] = 1;
        }
        if (a % 1000 == 0) {
            printf("%d%% complete\n", a * 100 / steps);
        }
    }

    free(particles);

    return buffer;
}

void write_streamlines_to_ppm(vector_field_t *vectors, int *streamlines, char *output_file) {
    uint32_t width = vectors->field_width;
    uint32_t height = vectors->field_height;

    FILE *fptr = fopen(output_file, "w");

    fprintf(fptr, "P5 %d %d %d\n", width, height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int i = get_index(width, height, (int) x, (int) y);
            int streamlines_val = streamlines[i];

            fputc(streamlines_val, fptr);
        }
    }

    fclose(fptr);
    fptr = NULL;

    return;
}
