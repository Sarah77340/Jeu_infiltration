/* CROZAT Alex
* Proper number generation module.
*/

#ifndef L3_RANDOM
#define L3_RANDOM

#include <stdlib.h>
#include <time.h>

int init_random();

float random_seed();

int L3_randint(int min, int max);

float L3_random(float min, float max);

#endif