/* CROZAT Alex
NGUYEN Sarah
Dynamic array definition module
*/

#include "../include/dynamic_array.h"
#include <assert.h>
#include <stdio.h>

#define NULL ((void *)0)

/**
 * @brief Inserts point in array
 * 
 * @param tile 
 * @param s
 * @return int 
 */
int push(Coords coords, DynamicArray * s){
    assert(&coords != NULL);
    assert(s != NULL);
    s->array[s->size] = coords;
    s->size++;
    return 0;
}

/**
 * @brief Removes point in index "index" from the array
 * 
 * @param tile 
 * @param s
 * @return int 
 */
int pop(Coords * coords, DynamicArray * s, int index){
    assert(s != NULL);
    *coords = s->array[index];
    s->array[index] = s->array[s->size-1];
    s->size--;
    return 0;
}

/**
 * @brief Removes random point in array
 * 
 * @param tile 
 * @param s
 * @return int 
 */
int pop_random(Coords * coords, DynamicArray * s){
    int index;
    assert(s != NULL);
    index = L3_randint(0,s->size-1);
    pop(coords,s,index);
    return 0;
}

/**
 * @brief Prints stack
 * 
 * @param s
 * @return int 
 */
void print_dynamic_array(DynamicArray s){
    int i;
    printf("Stack: ");
    for(i = 0; i < s.size; i++){
        printf("%d %d; ", s.array[i].i, s.array[i].j);
    }
    printf("size : %d\n", s.size);
}