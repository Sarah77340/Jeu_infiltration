#ifndef DISPLAY
#define DISPLAY

#include "game.h"
#include "leaderboard.h"
#include <MLV/MLV_all.h>


#define GREEN MLV_COLOR_GREEN
#define BLUE MLV_COLOR_BLUE
#define RED MLV_COLOR_RED
#define GRAY MLV_COLOR_DARK_GREY
#define BLACK MLV_COLOR_BLACK
#define CYAN MLV_COLOR_DARK_TURQUOISE
#define MOSS_GREEN MLV_COLOR_SEA_GREEN
#define GOLD MLV_COLOR_GOLD
#define BROWN MLV_COLOR_BROWN
#define RED_PANIC MLV_COLOR_DARK_RED

#define TILE_SIZE 10 /*20*/
#define FRAMES_PER_SECOND STEPS

#define DIRECTIONAL_KEYS_NUMBER 8
#define Z_KEY MLV_KEYBOARD_z
#define Q_KEY MLV_KEYBOARD_q
#define S_KEY MLV_KEYBOARD_s
#define D_KEY MLV_KEYBOARD_d
#define UP_KEY MLV_KEYBOARD_UP
#define DOWN_KEY MLV_KEYBOARD_DOWN
#define LEFT_KEY MLV_KEYBOARD_LEFT
#define RIGHT_KEY MLV_KEYBOARD_RIGHT
#define LSHIFT_KEY MLV_KEYBOARD_LSHIFT
#define RSHIFT_KEY MLV_KEYBOARD_RSHIFT
#define SPACE_KEY MLV_KEYBOARD_SPACE



#define MENU_BUTTON_PLAY_X TILE_SIZE * TERRAIN_WIDTH / 3
#define MENU_BUTTON_PLAY_Y TILE_SIZE * TERRAIN_HEIGHT / 4
#define MENU_BUTTON_PLAY_WIDTH TILE_SIZE * TERRAIN_WIDTH / 3
#define MENU_BUTTON_PLAY_HEIGHT TILE_SIZE * TERRAIN_HEIGHT / 7
#define MARGIN TILE_SIZE * 9

#define FILE_BLOC_SIZE 3
#define FILE_BLOC_COUNT 1

int init_window();
int display_menu();
int display_game_win(char ** name);
int display_game_lost();
int display_ranking_score(Leaderboard * board);
int display_game_information(Game * g);
int display_terrain(Terrain * terrain);
int display_entity(Entity* e);
int WaitClick();
int WaitClickOnBox(int x0, int y0, int w, int h);


int released_move_key(Game * g, MLV_Button_state state);
int control_player_with_keyboard(Game * g);

void color_background(MLV_Color color, Terrain* t);

#endif
