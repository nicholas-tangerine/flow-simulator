#include <math.h>

#include "vectors.h"
#include "math_helper.h"

double g(double alpha, double nu, double r) {
    return 1 - exp((-alpha * r * r) / (2 * nu));
}

vector_field_t *burgers_vortex(double alpha, double gamma, double nu, uint32_t width, uint32_t height, uint32_t center_x, uint32_t center_y) {
    vector_field_t *vectors = vector_field_init(width, height);

    for (int j = 0; j < (int) height; j++) {
        for (int i = 0; i < (int) width; i++) {
            int x = (i - (int) center_x);
            int y = (j - (int) center_y);
            int index = get_index(width, height, i, j);

            double r = sqrt( (double) (x*x) + (double) (y*y) );

            double v_r = -1 * alpha * r;
            double v_theta = (gamma * g(alpha, nu, r)) / (2 * (double) M_PI * r);

            double v_x, v_y;

            if (r == 0) {
                v_x = 0;
                v_y = 0;
            }
            else {
                v_x = (v_r * (double) x / r) - (v_theta * (double) y / r);
                v_y = (v_r * (double) y / r) + (v_theta * (double) x / r);
            }

            vectors->x_component[index] = v_x;
            vectors->y_component[index] = v_y;
        }
    }

    return vectors;
}
