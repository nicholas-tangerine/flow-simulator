#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vectors.h"

vector_field_t *vector_field_init(uint32_t width, uint32_t height) {
    vector_field_t *vectors = (vector_field_t *) calloc(1, sizeof(vector_field_t));

    vectors->field_width = width;
    vectors->field_height = height;
    vectors->field_area = width * height;

    vectors->x_component = calloc(width * height, sizeof(double));
    vectors->y_component = calloc(width * height, sizeof(double));

    for (int i = 0; i < (int) width * (int) height; i++) {
        vectors->x_component[i] = 0.0f;
        vectors->y_component[i] = 0.0f;
    }

    return vectors;
}

vector_field_t *vector_field_init_random(uint32_t width, uint32_t height) {
    vector_field_t *vectors = (vector_field_t *) calloc(1, sizeof(vector_field_t));

    vectors->field_width = width;
    vectors->field_height = height;
    vectors->field_area = width * height;

    vectors->x_component = calloc(width * height, sizeof(double));
    vectors->y_component = calloc(width * height, sizeof(double));

    for (int i = 0; i < (int) width * (int) height; i++) {
        double x = (double) rand();
        double y = (double) rand();

        x *= ((int) rand() % 2 == 0 ? 1 : -1);
        y *= ((int) rand() % 2 == 0 ? 1 : -1);

        double magnitude = sqrt(x*x + y*y);
        x /= magnitude;
        y /= magnitude;

        vectors->x_component[i] = x;
        vectors->y_component[i] = y;

    }

    return vectors;
}

void vector_field_normalize(vector_field_t *vectors) {
    double max_magnitude = 0.0f;

    uint32_t width = vectors->field_width;
    uint32_t height = vectors->field_height;

    for (int i = 0; i < (int) (width * height); i++) {
        double v_x = vectors->x_component[i];
        double v_y = vectors->y_component[i];

        double curr_magnitude = ((v_x*v_x) + (v_y*v_y));
        max_magnitude = curr_magnitude > max_magnitude ? curr_magnitude : max_magnitude;
    }

    double scale = 1 / max_magnitude;

    for (int i = 0; i < (int) (width * height); i++) {
        vectors->x_component[i] *= scale;
        vectors->y_component[i] *= scale;
    }
}

void vector_field_free(vector_field_t *vectors) {
    free(vectors->x_component);
    free(vectors->y_component);
    free(vectors);
    /*
    vector_field_t *field = *vectors;

    free(field->x_component);
    free(field->y_component);

    free(*vectors);
    *vectors = NULL;
    */

    return;
}

scalar_field_t *scalar_field_init(uint32_t width, uint32_t height) {
    scalar_field_t *scalars = (scalar_field_t *) calloc(1, sizeof(scalar_field_t));

    scalars->field_width = width;
    scalars->field_height = height;
    scalars->field_area = width * height;

    scalars->scalars = calloc(width * height, sizeof(double));

    return scalars;
}

scalar_field_t *scalar_field_init_random(uint32_t width, uint32_t height) {
    scalar_field_t *scalars = (scalar_field_t *) calloc(1, sizeof(scalar_field_t));

    scalars->field_width = width;
    scalars->field_height = height;
    scalars->field_area = width * height;

    scalars->scalars = calloc(width * height, sizeof(double));

    for (uint32_t i = 0; i < scalars->field_area; i++) {
        scalars->scalars[i] = (double) rand() / RAND_MAX;
    }

    return scalars;
}

void scalar_field_free(scalar_field_t **scalars) {
    scalar_field_t *field = *scalars;

    free(field->scalars);
    free(*scalars);

    *scalars = NULL;

    return;
}
