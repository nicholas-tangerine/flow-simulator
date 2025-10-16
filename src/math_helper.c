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
