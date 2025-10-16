#include <stdlib.h>
#include <math.h>

#include "math_helper.h"
#include "vectors.h"
#include "noise.h"

#define PERLIN_PIXELS_PER_GRID 5

double generate_intensity_point(vector_field_t *perlin_field, int x_intensity_idx, int y_intensity_idx) {
    uint32_t width = perlin_field->field_width;
    uint32_t height = perlin_field->field_height;
    uint32_t perlin_width = width / PERLIN_PIXELS_PER_GRID;
    uint32_t perlin_height = height / PERLIN_PIXELS_PER_GRID;

    double *u_field = perlin_field->x_component;
    double *v_field = perlin_field->y_component;

    int perlin_x_top_left = x_intensity_idx / PERLIN_PIXELS_PER_GRID;
    int perlin_y_top_left = y_intensity_idx / PERLIN_PIXELS_PER_GRID;

    int vector_top_left_idx = get_index(perlin_width, perlin_height, perlin_x_top_left, perlin_y_top_left);
    int vector_top_righ_idx = get_index(perlin_width, perlin_height, perlin_x_top_left+1, perlin_y_top_left);
    int vector_bot_left_idx = get_index(perlin_width, perlin_height, perlin_x_top_left, perlin_y_top_left+1);
    int vector_bot_righ_idx = get_index(perlin_width, perlin_height, perlin_x_top_left+1, perlin_y_top_left+1);
    
    double dx_top_left = x_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left);
    double dy_top_left = y_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left);
    double mag1 = sqrt(dx_top_left*dx_top_left + dy_top_left*dy_top_left);
    dx_top_left /= mag1;
    dy_top_left /= mag1;

    double dx_top_righ = x_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left) + 1;
    double dy_top_righ = y_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left);
    double mag2 = sqrt(dx_top_righ*dx_top_righ + dy_top_righ*dy_top_righ);
    dx_top_righ /= mag2;
    dy_top_righ /= mag2;


    double dx_bot_left = x_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left);
    double dy_bot_left = y_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left) + 1;
    double mag3 = sqrt(dx_bot_left*dx_bot_left + dy_bot_left*dy_bot_left);
    dx_bot_left /= mag3;
    dy_bot_left /= mag3;

    double dx_bot_righ = x_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left) + 1;
    double dy_bot_righ = y_intensity_idx - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left) + 1;
    double mag4 = sqrt(dx_bot_righ*dx_bot_righ + dy_bot_righ*dy_bot_righ);
    dx_bot_righ /= mag4;
    dy_bot_righ /= mag4;

    double intensity = 0.0;
    intensity += dot_prod(dx_top_left, dy_top_left, u_field[vector_top_left_idx], v_field[vector_top_left_idx]);
    intensity += dot_prod(dx_top_righ, dy_top_righ, u_field[vector_top_righ_idx], v_field[vector_top_righ_idx]);
    intensity += dot_prod(dx_bot_left, dy_bot_left, u_field[vector_bot_left_idx], v_field[vector_bot_left_idx]);
    intensity += dot_prod(dx_bot_righ, dy_bot_righ, u_field[vector_bot_righ_idx], v_field[vector_bot_righ_idx]);

    return intensity /= 4;
}

double *generate_intensity_field(uint32_t width, uint32_t height) {
    uint32_t perlin_width = width / PERLIN_PIXELS_PER_GRID;
    uint32_t perlin_height = height / PERLIN_PIXELS_PER_GRID;

    vector_field_t *perlin_field = vector_field_init(perlin_width, perlin_height);

    double *u_field = perlin_field->x_component;
    double *v_field = perlin_field->y_component;
    double *intensity_buffer = calloc(width * height, sizeof(double));

    for (int y = 0; y < (int) height; y++) {
        for (int x = 0; x < (int) width; x++) {
            int intensity_index = get_index(width, height, x, y);
            double intensity_val = generate_intensity_point(perlin_field, x, y);

            intensity_buffer[intensity_index] = intensity_val;
        }
    }

    return intensity_buffer;
}
