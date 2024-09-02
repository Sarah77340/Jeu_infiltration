#include "../include/display.h"
#include "../include/terrain.h"
#include "../include/game.h"

#define _POSIX_C_SOURCE 199309L

int main(){
    double frametime, extratime;
    int quit=0;
    int win=0;
    int n;
    char * name;
    Leaderboard * board = NULL;

    /* Initialize game */
    struct timespec end_time, new_time;
    Game * game = init_game();
    init_window();

    /* Menu */
    display_menu();
    MLV_actualise_window();
    while(!WaitClick());

    /* Game */
    display_game_information(game);

    /* Initial terrains */
    display_terrain(game->terrain);

    /* Player */
    display_entity (game->player);

    /* Guardians */
    for(n=0;n<GUARDIANS_NUMBER;n++) {
        display_entity(game->guardians[n]);
    }

    MLV_actualise_window();
    /* Replace with a countdown */

    WaitClick();

    while(!quit) {
        game->time = MLV_get_time();
        clock_gettime(CLOCK_REALTIME, &end_time);

        /* Drawing operations */
        display_terrain(game->terrain);
        if(game->panic_steps>0) {
            color_background(RED_PANIC,game->terrain);
        }
        display_game_information(game);
        display_entity(game->player);
        for(n=0;n<GUARDIANS_NUMBER;n++) {
            display_entity(game->guardians[n]);
        }
        MLV_actualise_window();
       
        /* Dealing with the events */
        /* Win */
        win = check_win(game);
        if(win) {
            quit = 1;
            break;
        }

        /* Guardians sight */
        quit = guardians_vision(game);

        /* Panic mode handling */
        if(game->panic_steps>0) {
            game->panic_steps--;
            if(game->panic_steps==0) {
                toggle_normal(game);
            }
        }

        /* Get keyboard event and move player */
        control_player_with_keyboard(game);

        /* Checking collisions and moving guardians */
        for(n=0;n<GUARDIANS_NUMBER;n++) {
            Point p_col = collision_bound(game->terrain, game->guardians[n]);
            if(game->panic_steps==0) {
                move_normal_guardian(game->guardians[n], p_col);
            } else {
                move_panic_guardian(game->guardians[n], p_col);
            }
        }

        /* Framerate handling */
        clock_gettime(CLOCK_REALTIME, &new_time);
        frametime = new_time.tv_sec - end_time.tv_sec;
        frametime += (new_time.tv_nsec - end_time.tv_nsec) / 1.0E9;
        extratime = (1.0 / STEPS) - frametime;
        if(extratime > 0) {
            MLV_wait_milliseconds((int)(extratime * 1000));
        }
    }
    if(win) {
        /*** ask name ***/
        display_game_win(&name);
        MLV_actualise_window();

        /*** leaderboard ***/
        board = init_leaderboard();
        save_data_in_file(name, game->mana, game->time);
        read_data_in_file(board);
        rank_leaders_score(board);
        rank_leaders_time(board);

        /*** display ranking ***/
        display_ranking_score(board);
        MLV_actualise_window();
        WaitClick();
    } else {
        display_game_lost();
        MLV_actualise_window();
    }
    WaitClick();
    free_leaderboard(board);
    free_game(game);
    MLV_free_window();
    return 0;
}