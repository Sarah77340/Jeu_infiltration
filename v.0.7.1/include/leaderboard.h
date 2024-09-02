#ifndef LEADERBOARD
#define LEADERBOARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTER_NAME 20
#define NUMBER_MAX_LEADER_DISPLAY 15

typedef struct leader{
    int score;
    int time;
    char * name;
} Leader;

typedef struct leaderboard{
    Leader ** array;
    int size;
    int * ranking_score_index;
    int * ranking_time_index;
    
} Leaderboard;

Leaderboard * init_leaderboard();
Leader * init_leader(int score, int time, char * name);
void free_leaderboard(Leaderboard * b);
int add_new_leader(Leaderboard * board, int score, int time, char ** name);
int read_leaderboard(Leaderboard * board);
int read_ranking_score_index(Leaderboard * board);
int read_ranking_time_index(Leaderboard * board);
int rank_leaders_score(Leaderboard * board);
int rank_leaders_time(Leaderboard * board);

FILE * get_file(const char * path, const char * accessMode);
int save_data_in_file(char * name, int score, int time);
int read_data_in_file();

#endif