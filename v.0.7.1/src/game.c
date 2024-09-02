/* CROZAT Alex
NGUYEN Sarah
Game handling module
*/

#include "../include/game.h"

/**
 * @brief Allocates memory for game.
 *
 * @return Game * 
 */
Game * init_game(){
    int n;
    Game * g = (Game*)malloc(sizeof(Game));
    if (g == NULL){
        fprintf(stderr, "erreur allocation sur p\n");
        return NULL;
    }
    init_random();
    g->terrain = init_terrain();
    generate_terrain(g->terrain);

    g->player = init_entity(PLAYER);
    for(n=0;n<GUARDIANS_NUMBER;n++) {
        g->guardians[n] = init_entity(GUARDIAN);
        place_guardian(g->terrain, g->guardians[n]);
    }
    g->mana = 0;
    g->time = 0;
    g->available_relics = RELIC_NUMBER;
    /*g->mode = NORMAL;*/
    g->panic_steps = 0;
    g->invisibility=0;
    g->overdrive=0;
    return g;
}

/**
 * @brief Deallocates memory for game
 *
 * @param g
 */
void free_game(Game * g){
    int i;
    if(g == NULL){
        return;
    }
    free(g->terrain);
    free(g->player);
    for(i = 0; i < GUARDIANS_NUMBER; i++){
        free(g->guardians[i]);
        g->guardians[i] = NULL;
    }
    g->terrain = NULL;
    g->player = NULL;
    free(g);
    g = NULL;
}

/**
 * @brief Updates tiles collected by player 
 * 
 * @param g 
 * @return int 
 */
int collect(Game * g){
    int i_col, j_col;
    Coords coords;
    assert(g != NULL);
    i_col = (int)g->player->x; 
    j_col = (int)g->player->y;
    coords.i = i_col;
    coords.j = j_col;
    /* MANA */
    if((g->terrain->tiles)[i_col][j_col] == MANA){
        push(coords, &(g->terrain->collected_mana));
        (g->terrain->tiles)[i_col][j_col] = GROUND;
        g->mana += 1;
    }
    /* RELIC */
    else if((g->terrain->tiles)[i_col][j_col] == RELIC) {
        g->available_relics -= 1;
        push(coords, &(g->terrain->stolen_relics));
        (g->terrain->tiles)[i_col][j_col] = STOLEN_RELIC;
    }
    return 0;
}

/**
 * @brief Adjusts player speed and update its position
 * 
 * @param g 
 * @param direction
 * @return int 
 */
int move_player(Game * g, Cardinal direction){
    Point p_col;
    assert(g != NULL);

    if(g->player->direction == direction && g->overdrive){
        player_manage_speed(g, OVERDRIVE);
    }
    else if(g->player->direction == direction && !(g->overdrive)){
        player_manage_speed(g, SPEED_UP);
    }
    else{
        g->player->direction = direction;
        player_manage_speed(g, MOVE_START);
    }
    p_col = collision_bound(g->terrain, g->player);
    update_entity_position(g->player, p_col);
    return 0;
}

/**
 * @brief Manages player speed
 * 
 * @param g 
 * @param choice
 * @return int 
 */
int player_manage_speed(Game * g, int choice){
    assert(g != NULL);

    switch(choice){
        case MOVE_START: /* startup or change direction */ 
            g->player->speed = SPEED * PLAYER_MIN_SPEED;
            break;
        case SPEED_UP: /* speed up */ 
            if(g->player->speed < SPEED * PLAYER_MAX_SPEED){
                g->player->speed += SPEED * PLAYER_ACCELERATION;
            }
            if(g->player->speed > SPEED * PLAYER_MAX_SPEED) {
                g->player->speed = SPEED * PLAYER_MAX_SPEED;
            }
            break;
        case OVERDRIVE: /* overdrive */ 
            if(g->mana > 1 && g->player->speed < SPEED * PLAYER_MAX_OVERDRIVE_SPEED){
                g->player->speed += SPEED * PLAYER_ACCELERATION;
                g->mana -= 2;
                generate_mana(g->terrain, 2);
            }
            if(g->player->speed > SPEED * PLAYER_MAX_OVERDRIVE_SPEED) {
                g->player->speed = SPEED * PLAYER_MAX_OVERDRIVE_SPEED;
            }
            break;
    }
    return 0;
}

/**
 * @brief Turns all guardians into panic guardians
 * 
 * @param g 
 * @return int 
 */
void trigger_panic(Game * g) {
    int n;
    for(n=0;n<GUARDIANS_NUMBER;n++) {
        g->guardians[n]->type = PANIC_GUARDIAN;
        g->guardians[n]->speed = SPEED * PANIC_GUARDIAN_SPEED;
    }
    g->panic_steps = PANIC_TIME * STEPS + 1;
}

/**
 * @brief Returns all guardians into their normal guardian state
 * 
 * @param g 
 * @return int 
 */
void toggle_normal(Game * g) {
    int n;
    for(n=0;n<GUARDIANS_NUMBER;n++) {
        g->guardians[n]->type = GUARDIAN;
        g->guardians[n]->speed = SPEED * L3_random(GUARDIAN_MIN_SPEED,GUARDIAN_MAX_SPEED);
    }    
}

/**
 * @brief Checks whether the game has been won by the player
 * 
 * @param g 
 * @return int 
 */
int check_win(Game* g) {
    return(g->terrain->tiles[(int)(g->player->x)][(int)(g->player->y)]==ENTRANCE&&g->available_relics==0);
}

/**
 * @brief Handles guardians vision of players and stolen relics.
 * 
 * @param g 
 * @return int (quit)
 */
int guardians_vision(Game* g) {
    int n,r;
    int sight = (g->panic_steps>0) ? PANIC_GUARDIAN_SIGHT : GUARDIAN_SIGHT;
    for(n=0;n<GUARDIANS_NUMBER;n++) {
        /* Stolen relic spotted ? Panic mode activated */
        for(r=0;r<g->terrain->stolen_relics.size;r++) {
            Coords relic_position = g->terrain->stolen_relics.array[r];
            if(euclidian_distance(g->guardians[n]->x,g->guardians[n]->y,relic_position.i+0.5,relic_position.j+0.5)<sight) {
                if(point_spotted(g->guardians[n]->x,g->guardians[n]->y,relic_position.i+0.5,relic_position.j+0.5,g->terrain)) {
                    Coords relic_coords;
                    trigger_panic(g);
                    pop(&relic_coords,&(g->terrain->stolen_relics),r);
                    r+=RELIC_NUMBER;
                }
            }
        }
        /* Noticing a player ? Game over ! Guardians cannot notice an invisible player. */
        if(!(g->invisibility)&&(euclidian_distance(g->guardians[n]->x,g->guardians[n]->y,g->player->x,g->player->y)<sight)) {
            return(point_spotted(g->player->x,g->player->y,g->guardians[n]->x,g->guardians[n]->y,g->terrain));
        }
    }
    return 0;
}