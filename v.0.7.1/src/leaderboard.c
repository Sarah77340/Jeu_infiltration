/* 
NGUYEN Sarah
Display handling module
*/

#include "../include/leaderboard.h"

/**
 * @brief Allocates memory for leaderboard.
 *
 * @return Leaderboard * 
 */
Leaderboard * init_leaderboard(){
    Leaderboard * l = (Leaderboard*)malloc(sizeof(Leaderboard));
    if (l == NULL){
        fprintf(stderr, "erreur allocation sur p\n");
        return NULL;
    }
    l->size = 0;
    l->ranking_score_index = (int*)malloc(sizeof(int));
    l->ranking_time_index = (int*)malloc(sizeof(int));
    return l;
}

/**
 * @brief Allocates memory for leader
 *
 * @param score 
 * @param time 
 * @param name 
 * @return Leader * 
 */
Leader * init_leader(int score, int time, char * name){
    Leader * l;
    assert(name != NULL);
    l = (Leader*)malloc(sizeof(Leader));
    if (l == NULL){
        fprintf(stderr, "erreur allocation sur p\n");
        return NULL;
    }
    l->score = score;
    l->time = time;
    l->name = name;
    return l;
}

/**
 * @brief Deallocates memory for leaderboard
 *
 * @param b 
 */
void free_leaderboard(Leaderboard * b){
    int i;
    if(b == NULL){
        return;
    }
    for(i = 0; i < b->size; i++){
        free(b->array[i]);
        b->array[i] = NULL;
    }
    free(b->ranking_score_index);
    free(b->ranking_time_index);

    b->ranking_score_index = NULL;
    b->ranking_time_index = NULL; 
    free(b);
    b = NULL;
}

/**
 * @brief Adds a new leader in leaderboard's array
 *
 * @param board
 * @param score 
 * @param time 
 * @param name 
 * @return int 
 */
int add_new_leader(Leaderboard * board, int score, int time, char ** name){
    char* copy_name;
    assert(board != NULL);
    if(score < 0 || time < 0 || name == NULL){
        fprintf(stderr, "Data not correct\n");
        return 1;
    }
    copy_name = (char *) malloc(MAX_CHARACTER_NAME * sizeof(int));
    if(copy_name == NULL){
        fprintf(stderr, "Allocation memory for copy_name failed\n");
        return 2;
    }
    memcpy(copy_name, name, MAX_CHARACTER_NAME * sizeof(int));
    board->array[board->size] = init_leader(score, time, copy_name);
    board->ranking_score_index[board->size] = board->size;
    board->ranking_time_index[board->size] = board->size;
    board->size++;
    return 0;
}

/**
 * @brief Prints leaderboard
 *
 * @param board
 * @return int 
 */
int read_leaderboard(Leaderboard * board){
    int i;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    for(i = 0; i < board->size; i++){
        printf("%s: score: %d  time: %d\n",  board->array[i]->name, 
        board->array[i]->score, board->array[i]->time);
    }
    return 0;
}

/**
 * @brief Prints ranking_score_index
 *
 * @param board
 * @return int 
 */
int read_ranking_score_index(Leaderboard * board){
    int i, index;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    printf("Rank by score:\n");
    for(i = 0; i < board->size; i++){
        index = board->ranking_score_index[i];
        printf("index: %d, score: %d\n", index, 
        board->array[index]->score);
    }
    return 0;
}

/**
 * @brief Prints ranking_time_index
 *
 * @param board
 * @return int 
 */
int read_ranking_time_index(Leaderboard * board){
    int i, index;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    printf("Rank by time:\n");
    for(i = 0; i < board->size; i++){
        index = board->ranking_time_index[i];
        printf("index: %d, time: %d\n", index, 
        board->array[index]->time);
    }
    return 0;
}

/**
 * @brief Ranks index in ranking_score_index by highest score in descending order
 *
 * @param board
 * @return int 
 */
int rank_leaders_score(Leaderboard * board){
    int tmp, i, j;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    for(i = 0; i < board->size; i++){
        for(j = 0; j < board->size; j++){
            if(board->array[board->ranking_score_index[i]]->score 
            > board->array[board->ranking_score_index[j]]->score){
                tmp = board->ranking_score_index[i];
                board->ranking_score_index[i] = board->ranking_score_index[j];
                board->ranking_score_index[j] = tmp;
            }
        }
    }
    return 0;
}

/**
 * @brief Ranks index in ranking_time_index by shortest time in ascending order
 *
 * @param board
 * @return int 
 */
int rank_leaders_time(Leaderboard * board){
    int tmp, i, j;
    assert(board != NULL);
    if(board->size <= 0){
        printf("nothing to read\n");
        return 1;
    }
    for(i = 0; i < board->size; i++){
        for(j = 0; j < board->size; j++){
            if(board->array[board->ranking_time_index[i]]->time 
            < board->array[board->ranking_time_index[j]]->time){
                tmp = board->ranking_time_index[i];
                board->ranking_time_index[i] = board->ranking_time_index[j];
                board->ranking_time_index[j] = tmp;
            }
        }
    }
    return 0;
}

/**
 * @brief Opens file
 *
 * @param path
 * @param accessMode
 * @return File * 
 */
FILE * get_file(const char * path, const char * accessMode){
    FILE *df;
    assert(path != NULL);
    assert(accessMode != NULL);
    df = fopen(path, accessMode);
    if(df == NULL){
        /*fprintf(stderr, "Can't open file\n");*/
        exit(1);
    }
    return df;
}

/**
 * @brief Write data to file
 *
 * @param name
 * @param score
 * @param time
 * @return int 
 */
int save_data_in_file(char * name, int score, int time){
    FILE * file1;
    if(score < 0 || time < 0){
        fprintf(stderr, "Data not correct\n");
        return 1;
    }
    file1 = get_file("bin/classement.bin", "ab");
    fwrite(&score, sizeof(int), 1, file1);
    fwrite(&time, sizeof(int), 1, file1);
    fwrite(name, MAX_CHARACTER_NAME * sizeof(int), 1, file1); 
    fclose(file1);
    /*printf("memory added: %ld\n", sizeof(int)+ sizeof(int) + (MAX_CHARACTER_NAME * sizeof(int)));*/
    return 0;
}

/**
 * @brief Reads data in file and adds to leaderboard
 *
 * @param board
 * @return int 
 */
int read_data_in_file(Leaderboard * board){
    int score, time;
    char * name[MAX_CHARACTER_NAME];
    FILE * file = get_file("bin/classement.bin", "rb");
    while(!feof(file)) {
        if(!fread(&score, sizeof(int), 1, file) || 
            !fread(&time, sizeof(int), 1, file) ||
            !fread(&name, MAX_CHARACTER_NAME * sizeof(int), 1, file)){
                break;
            }
        /*printf("score: %d, time: %d name: %s\n", score, time, name);*/
        add_new_leader(board, score, time, name);
    }
    fclose(file);
    return 0;
}

