#include <stdlib.h>

#include "math_helper.h"

int get_index(uint32_t width, uint32_t height, int x, int y) {
    x = x < 0 ? -x : x;
    x = x >= (int) width ? (int) width - (x - (int) width + 1) : x;

    y = y < 0 ? -y : y;
    y = y >= (int) height ? (int) height - (y - (int) height + 1) : y;

    return y * (int) width + x;
}

double dot_prod(double x1, double x2, double y1, double y2) {
    return x1*y1 + x2*y2;
}

double lerp(double x, double y, double u) {
    //  `U` MUST BE NORMALIZED BETWEEN 0 AND 1

    return u * x + (1-u) * y;

}

double fade(double t) {
    // Perlin's smoothstep function: 6t^5 - 15t^4 + 10t^3
    // This has zero first and second derivatives at t=0 and t=1
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}
