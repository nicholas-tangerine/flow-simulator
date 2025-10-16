#include <stdlib.h>
#include <stdio.h>

#include "noise.h"
#include "vectors.h"
#include "particle.h"
#include "debug_utils.h"

#define IMAGE_WIDTH 1800
#define IMAGE_HEIGHT (IMAGE_WIDTH / 2)

#define PARTICLES_PER_ROW 100
#define PARTICLES_PER_COL (PARTICLES_PER_ROW / 2)
#define STREAMLINES_ITERATIONS 40
#define STREAMLINES_DT 3.0

int main(int argc, char **argv) {
    vector_field_t *vector_field = vector_field_init(IMAGE_WIDTH + 1, IMAGE_HEIGHT + 1);
    scalar_field_t *scalar_field = scalar_field_init(IMAGE_WIDTH, IMAGE_HEIGHT);

    int *streamlines = draw_streamlines_to_buffer(vector_field, PARTICLES_PER_ROW, PARTICLES_PER_COL, STREAMLINES_ITERATIONS, STREAMLINES_DT);

    write_streamlines_to_ppm(vector_field, streamlines, "output.ppm");

    double *intensity_buffer = generate_intensity_field(IMAGE_WIDTH, IMAGE_HEIGHT);

    write_intensity_buffer_to_ppm(intensity_buffer, IMAGE_WIDTH, IMAGE_HEIGHT, "intensity.ppm");

    /**
     * FREE MEMORY
     */
    vector_field_free(&vector_field);
    scalar_field_free(&scalar_field);
    free(streamlines);
    free(intensity_buffer);

    return 0;
}
