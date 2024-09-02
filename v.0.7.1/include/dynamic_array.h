/* CROZAT Alex
NGUYEN Sarah
Dynamic array definition module
*/

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include "geometry.h"
#include "L3_random.h"

typedef struct dynamic_array {
    Coords *array;
    int size;
} DynamicArray;


int push(Coords coords, DynamicArray * s);
int pop(Coords * coords, DynamicArray * s, int index);
int pop_random(Coords * coords, DynamicArray * s);
void print_dynamic_array(DynamicArray s);

#endif