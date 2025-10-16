#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdint.h>

/**
 * Gets the index of a 2d array stored in contiguous memory. Mirrors into the 2d array if out of bounds
 *
 * @param width             array width
 * @param height            array height
 * @param x                 x coordinate of wanted index
 * @param y                 y coordinate of wanted index
 *
 * @return index            index in the contiguous memory
 */
int get_index(uint32_t width, uint32_t height, int x, int y);

/**
 * Calculates the dot product of two vectors, x and y. x1 is x component of x, and x2 is y component of y. Similar scheme for vector y
 *
 * @param x1
 * @param x2
 * @param y1
 * @param y2
 *
 * @return dot product of vectors x and y
 */
double dot_prod(double x1, double x2, double y1, double y2);

#endif
