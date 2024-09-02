/* CROZAT Alex
NGUYEN Sarah
Display handling module
*/

#include "../include/display.h"

/**
 * @brief Initializes the game window.
 * 
 * 
 */
int init_window(){
    MLV_create_window("Stealth", "Main Game", TILE_SIZE * TERRAIN_WIDTH + MARGIN, TILE_SIZE * TERRAIN_HEIGHT);
    /*MLV_clear_window(MLV_COLOR_DARK_GREY);*/
    return 0;
}

/**
 * @brief Draws a tile on the game window.
 * 
 * @param i Horizontal coordinates
 * @param j Vertical coordinates
 * @param color Color of the tile
 */
int draw_tile(int i, int j,MLV_Color color) {
    MLV_draw_filled_rectangle(TILE_SIZE * i + 1, TILE_SIZE * j + 1, TILE_SIZE - 1, TILE_SIZE - 1, color);
    return 0;
}

/**
 * @brief Draws the grid separating each tile.
 * 
 * @param grid_color 
 */
int draw_grid(MLV_Color grid_color) {
    int i,j;
    for(i=0; i < TERRAIN_HEIGHT; i++){
        for(j=0; j < TERRAIN_WIDTH; j++){
            MLV_draw_line(0, TILE_SIZE * i, TILE_SIZE * TERRAIN_WIDTH, TILE_SIZE * i, grid_color);
            MLV_draw_line(TILE_SIZE * j, 0, TILE_SIZE * j, TILE_SIZE * TERRAIN_HEIGHT, grid_color);
        }
    }
    return 0;
}

/**
 * @brief Displays menu.
 *
 */
int display_menu(){
    MLV_draw_text_box(MENU_BUTTON_PLAY_X, MENU_BUTTON_PLAY_Y, MENU_BUTTON_PLAY_WIDTH, MENU_BUTTON_PLAY_HEIGHT,
    "START", 3, CYAN, BLACK, CYAN, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    return 0;
}

/**
 * @brief Displays window when player won and ask username.
 *
 */
int display_game_win(char ** name){
    MLV_clear_window(BLACK);
    MLV_draw_text(TILE_SIZE, TILE_SIZE, "You won ! Congratulations!", CYAN);
    MLV_wait_input_box((TILE_SIZE * TERRAIN_WIDTH + MARGIN) / 2 - MARGIN, 
    TILE_SIZE * TERRAIN_HEIGHT / 2, MARGIN * 2, MARGIN / 2, CYAN, BLACK, CYAN, "username : ", name);
    return 0;
}

/**
 * @brief Displays window when player lost.
 *
 */
int display_game_lost(){
    MLV_clear_window(BLACK);
    MLV_draw_text(TILE_SIZE, TILE_SIZE, "Mission failed ! We'll get'em next time.", CYAN);
    return 0;
}

/**
 * @brief Displays ranking
 *
 */
int display_ranking_score(Leaderboard * board){
    int i, index_score, index_time, mini_margin, rec_x2, size, min1, sec1;
    float rec_width, rec_height;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    mini_margin = MARGIN / 2;
    rec_width = (TILE_SIZE * TERRAIN_WIDTH + MARGIN) / 2 - MARGIN;
    rec_height = (TILE_SIZE * TERRAIN_HEIGHT) - MARGIN;
    rec_x2 = mini_margin + rec_width + MARGIN;
    size = min(board->size, NUMBER_MAX_LEADER_DISPLAY);

    MLV_clear_window(BLACK);
    MLV_draw_rectangle(mini_margin, mini_margin, rec_width, rec_height, CYAN);
    MLV_draw_text(MARGIN, mini_margin + TILE_SIZE, "PLAYER", CYAN);
    MLV_draw_text(rec_width - mini_margin, mini_margin + TILE_SIZE, "MANA", CYAN);
    MLV_draw_rectangle(rec_x2, mini_margin, rec_width, rec_height, CYAN);
    MLV_draw_text(rec_x2 + mini_margin, mini_margin + TILE_SIZE, "PLAYER", CYAN);
    MLV_draw_text(rec_x2 + MARGIN * 2, mini_margin + TILE_SIZE, "TIME", CYAN);
    for(i = 0; i < size; i++){
        index_score = board->ranking_score_index[i];
        index_time = board->ranking_time_index[i];
        min1 = (int) board->array[index_time]->time / 1000 / 60;
        sec1 = (int) (board->array[index_time]->time / 1000 ) - min1 * 60;

        MLV_draw_text(MARGIN, TILE_SIZE * i * 2 + MARGIN, "%s", CYAN, board->array[index_score]->name);
        MLV_draw_text(rec_width - mini_margin, TILE_SIZE * i * 2 + MARGIN, "%d", CYAN, board->array[index_score]->score);
        MLV_draw_text(rec_x2 + mini_margin, TILE_SIZE * i * 2 + MARGIN, "%s", CYAN, board->array[index_time]->name);
        MLV_draw_text(rec_x2 + MARGIN * 2, TILE_SIZE * i * 2 + MARGIN, "%d:%d", CYAN, min1, sec1);
    }
    return 0;
}

/**
 * @brief Displays game information.
 * 
 * @param terrain 
 */
int display_game_information(Game * g){
    int min, sec;
    min = g->time / 1000 / 60;
    sec = (g->time / 1000 ) - min * 60;
    MLV_draw_filled_rectangle(TILE_SIZE * TERRAIN_WIDTH, 0, MARGIN, TILE_SIZE * TERRAIN_HEIGHT, BLACK);
    MLV_draw_text(TILE_SIZE * TERRAIN_WIDTH, TILE_SIZE, "score: %d", CYAN, g->mana);
    MLV_draw_text(TILE_SIZE * TERRAIN_WIDTH, TILE_SIZE * 3, "time: %d:%d", CYAN, min, sec);
    return 0;
}

/**
 * @brief Displays initial terrain.
 * 
 * @param terrain 
 */
int display_terrain(Terrain * terrain){
    int i, j;
    MLV_Color tile_colors[6] = {GRAY, BLACK, CYAN, MOSS_GREEN, GOLD, BROWN};
    assert(terrain != NULL);
    
    /* Draw initial grid */
    draw_grid(tile_colors[1]);

    /* Initialize tiles */
    for(i=0; i < TERRAIN_WIDTH; i++){
        for(j=0; j < TERRAIN_HEIGHT; j++) {
            MLV_Color color = tile_colors[ (terrain->tiles)[i][j] ];
            draw_tile(i,j,color);
        }
    }
    return 0;
}

/**
 * @brief Displays entity.
 * 
 * @param e 
 */
int display_entity(Entity* e){
    int i, j;
    MLV_Color entity_colors[3] = {GREEN,BLUE,RED};
    assert(e != NULL);

    i = (int) (TILE_SIZE * e->x);
    j = (int) (TILE_SIZE * e->y);

    MLV_draw_filled_circle(i,j, TILE_SIZE * e->r, entity_colors[e->type]);
    MLV_draw_circle(i,j, TILE_SIZE * e->r, BLACK);
    if((e->type)==GUARDIAN) {
        MLV_draw_circle(i,j, TILE_SIZE * GUARDIAN_SIGHT, entity_colors[e->type]);
    }
    if((e->type)==PANIC_GUARDIAN) {
        MLV_draw_circle(i,j, TILE_SIZE * PANIC_GUARDIAN_SIGHT, entity_colors[e->type]);
    }
    return 0;
}

int WaitClick() {
    int mouse_x, mouse_y;
    /*MLV_get_event(0, 0, 0, 0, 0, &mouse_x, &mouse_y, mouse_button,0);*/
    MLV_wait_mouse(&mouse_x, &mouse_y);

    if(mouse_x >= MENU_BUTTON_PLAY_X && mouse_x <= MENU_BUTTON_PLAY_X + MENU_BUTTON_PLAY_WIDTH
    && mouse_y >= MENU_BUTTON_PLAY_Y && mouse_y <= MENU_BUTTON_PLAY_Y + MENU_BUTTON_PLAY_HEIGHT){
        return 1;
    }
    /*MLV_flush_event_queue();*/
    return 0;
}

int WaitClickOnBox(int x0, int y0, int w, int h) {
    int mouse_x, mouse_y;
    /*MLV_get_event(0, 0, 0, 0, 0, &mouse_x, &mouse_y, mouse_button,0);*/
    MLV_wait_mouse(&mouse_x, &mouse_y);

    if(mouse_x >= x0 && mouse_x <= x0 + w
    && mouse_y >= y0 && mouse_y <= y0 + h){
        return 1;
    }
    /*MLV_flush_event_queue();*/
    return 0;    
}

/**
 * @brief Updates a parameter according to the state of two keys, input1 and input2.
 * 
 * @param input 
 * @param param 
 * @return int 
 */
int check_2_inputs(MLV_Keyboard_button input1, MLV_Keyboard_button input2, int * param) {
    if(MLV_get_keyboard_state(input1) == MLV_PRESSED ||
        MLV_get_keyboard_state(input2) == MLV_PRESSED){
        *param = 1;
    } else {
        *param = 0;
    }
    return 0;
}

/**
 * @brief Updates a parameter according to the state of a key input1.
 * 
 * @param input 
 * @param param 
 * @return int 
 */
int check_input(MLV_Keyboard_button input, int * param) {
    if(MLV_get_keyboard_state(input) == MLV_PRESSED){
        *param = 1;
    } else {
        *param = 0;
    }
    return 0;
}

int released_move_key(Game * g, MLV_Button_state state) {
    MLV_Keyboard_button dir_keys[DIRECTIONAL_KEYS_NUMBER] = {Z_KEY, UP_KEY, Q_KEY, LEFT_KEY, S_KEY, DOWN_KEY, D_KEY, RIGHT_KEY};
    int i;
    if(state==MLV_PRESSED) {
        return 0;
    }
    for(i=0;i<DIRECTIONAL_KEYS_NUMBER;i++) {
        if(MLV_get_keyboard_state(dir_keys[i]) == MLV_PRESSED) {
            return 0;
        }
    }
    return 1;
}

int control_player_with_keyboard(Game * g) {
    MLV_Keyboard_button keyboard;
    MLV_Button_state state;

    /* released */
    MLV_get_event(&keyboard, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
    /*
    if(state == MLV_RELEASED){
    */
    if(released_move_key(g,state)) {
        player_manage_speed(g, MOVE_START);
        return 2;
    }

    /* overdrive */
    check_2_inputs(RSHIFT_KEY,LSHIFT_KEY,&g->overdrive);

    /* invisibility */
    check_input(SPACE_KEY,&g->invisibility);
    if(g->invisibility) {
        if(g->mana > 1){
            g->mana -= 1;
            generate_mana(g->terrain, 1);
        } else {
            g->invisibility = 0;
        }
    }
    collect(g);

    if(MLV_get_keyboard_state(Z_KEY) == MLV_PRESSED ||
        MLV_get_keyboard_state(UP_KEY) == MLV_PRESSED){
        move_player(g, NORTH);

    } else if(MLV_get_keyboard_state(Q_KEY) == MLV_PRESSED ||
        MLV_get_keyboard_state(LEFT_KEY) == MLV_PRESSED){
        move_player(g, WEST);

    } else if(MLV_get_keyboard_state(D_KEY) == MLV_PRESSED ||
        MLV_get_keyboard_state(RIGHT_KEY) == MLV_PRESSED){
        move_player(g, EAST);

    } else if(MLV_get_keyboard_state(S_KEY) == MLV_PRESSED ||
        MLV_get_keyboard_state(DOWN_KEY) == MLV_PRESSED){
        move_player(g, SOUTH);
    }
    return 0;
}

/**
 * @brief Draws walls and grid with the new color
 * 
 * @param color 
 * @param t 
 * @return int 
 */
void color_background(MLV_Color color, Terrain* t) {
    /* Draw walls */
    int i,j;
    for(i=0;i<TERRAIN_WIDTH;i++) {
        for(j=0;j<TERRAIN_HEIGHT;j++) {
            if(t->tiles[i][j]==WALL) {
                draw_tile(i,j,color);
            }
        }
    }
    /* Draw grid*/
    draw_grid(color);
}