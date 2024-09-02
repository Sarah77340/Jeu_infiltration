/* NGUYEN Sarah
Game handling module
*/

#ifndef GAME
#define GAME

#include "entity.h"
#include "terrain.h"

#define GUARDIANS_NUMBER 5
#define PANIC_TIME 10

/*
typedef enum game_mode {
    NORMAL, PANIC
} GameMode;
*/

typedef struct game {
    int mana;
    int time;
    int available_relics;
    int invisibility;
    int overdrive;
    /*GameMode mode;*/
    int panic_steps;
    Entity * player; 
    Entity * guardians[GUARDIANS_NUMBER];
    Terrain * terrain;
} Game;

Game * init_game();
void free_game(Game * g);
int collect(Game * g);

int move_player(Game * g, Cardinal direction);
int player_manage_speed(Game * g, int choice);

void trigger_panic(Game * g);
void toggle_normal(Game * g);

int check_win(Game* g);

int guardians_vision(Game* g);

#endif