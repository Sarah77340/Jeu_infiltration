/* CROZAT Alex
* Distance calculation module, with basic math
*/

#ifndef GEOMETRY
#define GEOMETRY

#include <math.h>

#define min(a,b) ((a) < (b)) ? (a) : (b)

/*
#define min(a,b) fmin(a,b)
*/

/*
#define max(a,b) fmax(a,b)
*/
typedef struct point {
    float x;
    float y;
} Point;

typedef struct coords {
    int i;
    int j;
} Coords;

double euclidian_distance(double x_o, double y_o, double x, double y);

int max(int a, int b);

#endif