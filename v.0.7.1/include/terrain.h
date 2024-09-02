/* CROZAT Alex
NGUYEN Sarah
Terrain handling module
*/

#ifndef TERRAIN
#define TERRAIN

#include <stdio.h>
#include <assert.h>
#include "geometry.h"
#include "L3_random.h"
#include "dynamic_array.h"

#define TERRAIN_WIDTH 60
#define TERRAIN_HEIGHT 45
#define MINSIDE 9
#define DOOR_WIDTH 3 /* Must be inferior to minside */
#define RELIC_NUMBER 3
#define MIN_RELIC_SPAWN_DISTANCE 30

typedef enum tile {
    GROUND, WALL, MANA, ENTRANCE, RELIC, STOLEN_RELIC, RELIC_CANDIDATE
} Tile;

typedef struct terrain {
    Tile tiles[TERRAIN_WIDTH][TERRAIN_HEIGHT];
    DynamicArray collected_mana;
    DynamicArray stolen_relics;
} Terrain;


Terrain * init_terrain();

void cut_along_max_length(Terrain* terrain, int L_i, int l_i, int L_j, int l_j, int horizontal);

int make_inner_walls(Terrain* terrain, int x_i, int y_i, int x_j, int y_j);

int generate_relics(Terrain* terrain);
int generate_mana(Terrain* terrain, int nb_mana);
int generate_terrain(Terrain* terrain);

int point_spotted(float x_g, float y_g, float x_p, float y_p, Terrain* t);

#endif