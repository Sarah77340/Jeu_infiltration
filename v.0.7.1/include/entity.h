/* CROZAT Alex
NGUYEN Sarah
Entity handling module
*/

#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <assert.h>
#include "geometry.h"
#include "L3_random.h"
#include "terrain.h"

#define SPEED 15 /*Must be inferior to the number of steps.*/
#define STEPS 60 /*Number of computations per second.*/
#define RADIUS 0.5 /*Must be inferior to 1, the tile length.*/

#define PLAYER_MIN_SPEED 0.1
#define PLAYER_MAX_SPEED 0.9
#define PLAYER_MAX_OVERDRIVE_SPEED 1.2
#define PLAYER_ACCELERATION 0.03

#define MIN_GUARDIAN_SPAWN_RANGE 20
#define GUARDIAN_SIGHT 4
#define PANIC_GUARDIAN_SIGHT 6
#define GUARDIAN_MIN_SPEED 0.3
#define GUARDIAN_MAX_SPEED 0.8
#define PANIC_GUARDIAN_SPEED 1

#define GUARDIAN_TURNS 1.0 / 50

typedef enum type {
    PLAYER, GUARDIAN, PANIC_GUARDIAN
} Type;

typedef enum cardinal {
    NORTH, SOUTH, EAST, WEST
} Cardinal;

typedef enum move_type {
    MOVE_START, SPEED_UP, OVERDRIVE
} MoveType;

typedef struct entity {
    Cardinal direction;
    Type type;
    float x;
    float y;
    float r;
    float speed;
} Entity;

Entity * init_entity(Type type);

int update_entity_position(Entity* e, Point p_col);


int check_collision(Entity* e, Point p_max);

Point collision_bound(Terrain* t, Entity* e);


int place_guardian(Terrain* board, Entity* e);

int change_guardian_trajectory(Entity* e);

int move_normal_guardian(Entity* e, Point p_max);

int move_panic_guardian(Entity* e, Point p_max);

#endif