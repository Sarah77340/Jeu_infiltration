/* CROZAT Alex
* Proper number generation module.
*/

#include "../include/L3_random.h"

/**
 * @brief Initializes random library
 * 
 * @return int 
 */
int init_random() {
    srand(time(NULL));
    return 0;
}

/**
 * @brief Returns a nice random seed beteen 0 and 1.
 * 
 */
float random_seed() {
    return ((float)rand()/(float)(RAND_MAX));
}

/**
 * @brief Returns a nice random integer beteen min and max, both included.
 * 
 */
int L3_randint(int min, int max) {
    return min + random_seed() * (max - min + 1);
}

/**
 * @brief Returns a nice random float beteen min and max.
 * 
 */
float L3_random(float min, float max) {
    return min + random_seed() * (max - min);
}