/* CROZAT Alex
* Point and distance calculation module, with basic math
*/

#include "../include/geometry.h"

/**
 * @brief Computes the euclidian distance between point O (x_o,y_o) and point M (x,y)
 * 
 * @param x_o 
 * @param y_o 
 * @param x 
 * @param y 
 */
double euclidian_distance(double x_o, double y_o, double x, double y) {
    return sqrt((double)((x-x_o)*(x-x_o)+(y-y_o)*(y-y_o)));
}

int max(int a, int b) {
    return((a>b) ? a : b);
}