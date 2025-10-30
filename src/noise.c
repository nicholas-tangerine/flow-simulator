#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "math_helper.h"
#include "vectors.h"
#include "noise.h"

#define PERLIN_PIXELS_PER_GRID 120

double generate_intensity_point_perlin(vector_field_t *perlin_field, int intensity_x, int intensity_y) {
    uint32_t perlin_width = perlin_field->field_width;
    uint32_t perlin_height = perlin_field->field_height;

    double *perlin_u_field = perlin_field->x_component;
    double *perlin_v_field = perlin_field->y_component;

    int perlin_x_top_left = intensity_x / PERLIN_PIXELS_PER_GRID;
    int perlin_y_top_left = intensity_y / PERLIN_PIXELS_PER_GRID;

    int perlin_top_left_idx = get_index(perlin_width, perlin_height, perlin_x_top_left, perlin_y_top_left);
    int perlin_top_righ_idx = get_index(perlin_width, perlin_height, perlin_x_top_left+1, perlin_y_top_left);
    int perlin_bot_left_idx = get_index(perlin_width, perlin_height, perlin_x_top_left, perlin_y_top_left+1);
    int perlin_bot_righ_idx = get_index(perlin_width, perlin_height, perlin_x_top_left+1, perlin_y_top_left+1);
    
    double dx_top_left = (intensity_x - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left)) / (double)PERLIN_PIXELS_PER_GRID;
    double dy_top_left = (intensity_y - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left)) / (double)PERLIN_PIXELS_PER_GRID;

    double dx_top_righ = (intensity_x - (PERLIN_PIXELS_PER_GRID * (perlin_x_top_left + 1))) / (double)PERLIN_PIXELS_PER_GRID;
    double dy_top_righ = (intensity_y - (PERLIN_PIXELS_PER_GRID * perlin_y_top_left)) / (double)PERLIN_PIXELS_PER_GRID;

    double dx_bot_left = (intensity_x - (PERLIN_PIXELS_PER_GRID * perlin_x_top_left)) / (double)PERLIN_PIXELS_PER_GRID;
    double dy_bot_left = (intensity_y - (PERLIN_PIXELS_PER_GRID * (perlin_y_top_left + 1))) / (double)PERLIN_PIXELS_PER_GRID;

    double dx_bot_righ = (intensity_x - (PERLIN_PIXELS_PER_GRID * (perlin_x_top_left + 1))) / (double)PERLIN_PIXELS_PER_GRID;
    double dy_bot_righ = (intensity_y - (PERLIN_PIXELS_PER_GRID * (perlin_y_top_left + 1))) / (double)PERLIN_PIXELS_PER_GRID;

    double intensity = 0.0;
    double t1, t2, t3, t4;          //  temp variables

    t1 = dot_prod(dx_top_left, dy_top_left, perlin_u_field[perlin_top_left_idx], perlin_v_field[perlin_top_left_idx]);
    t2 = dot_prod(dx_top_righ, dy_top_righ, perlin_u_field[perlin_top_righ_idx], perlin_v_field[perlin_top_righ_idx]);
    
    // Calculate interpolation parameters with smooth fade function
    double u = fade(((double) intensity_x - (perlin_x_top_left * PERLIN_PIXELS_PER_GRID)) / PERLIN_PIXELS_PER_GRID);
    double v = fade(((double) intensity_y - (perlin_y_top_left * PERLIN_PIXELS_PER_GRID)) / PERLIN_PIXELS_PER_GRID);
    
    double top_interp = lerp(t2, t1, u);

    t3 = dot_prod(dx_bot_left, dy_bot_left, perlin_u_field[perlin_bot_left_idx], perlin_v_field[perlin_bot_left_idx]);
    t4 = dot_prod(dx_bot_righ, dy_bot_righ, perlin_u_field[perlin_bot_righ_idx], perlin_v_field[perlin_bot_righ_idx]);
    double bot_interp = lerp(t4, t3, u);

    intensity = lerp(bot_interp, top_interp, v);

    return intensity;
}

double *generate_intensity_field_perlin(uint32_t width, uint32_t height) {
    uint32_t perlin_width = width / PERLIN_PIXELS_PER_GRID+1;
    uint32_t perlin_height = height / PERLIN_PIXELS_PER_GRID+1;

    vector_field_t *perlin_field = vector_field_init_random(perlin_width, perlin_height);

    double *intensity_buffer = calloc(width * height, sizeof(double));

    for (int y = 0; y < (int) height; y++) {
        for (int x = 0; x < (int) width; x++) {
            int intensity_index = get_index(width, height, x, y);
            double intensity_val = generate_intensity_point_perlin(perlin_field, x, y);

            // Map from [-1, 1] to [0, 1]
            intensity_val = (intensity_val + 1.0) / 2.0;
            
            intensity_buffer[intensity_index] = intensity_val;
        }
    }

    return intensity_buffer;
}

