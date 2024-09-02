/* CROZAT Alex
NGUYEN Sarah
Terrain handling module
*/

#include "../include/terrain.h"
#include <math.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)

/**
* @brief Allocates memory for terrain
*/
Terrain * init_terrain(){
    Terrain * t = (Terrain*)malloc(sizeof(Terrain));
    if (t == NULL){
        fprintf(stderr, "erreur allocation sur p\n");
        return NULL;
    }
    t->collected_mana.array = (Coords*)malloc(sizeof(Coords)*(TERRAIN_WIDTH-2)*(TERRAIN_HEIGHT-2));
    t->collected_mana.size = 0;
    t->stolen_relics.array = (Coords*)malloc(sizeof(Coords)*RELIC_NUMBER);
    t->stolen_relics.size = 0;
    return t;
}

/**
 * @brief Generates two subrooms according to the longest room side by drawing an inner wall with a DOORSIZE opening.
 * 
 * @param terrain 
 * @param L_i 
 * @param l_i 
 * @param L_j 
 * @param l_j 
 * @param horizontal 
 */
void cut_along_max_length(Terrain* terrain, int L_i, int l_i, int L_j, int l_j, int horizontal) {
    int L_min = L_i + MINSIDE;
    int L_max = L_j - MINSIDE;
    int L_div = L_min + random_seed() * (L_max - L_min);
    float door_seed = random_seed();
    int anchor = (door_seed < 0.5) ? (l_j + 1 - DOOR_WIDTH) : l_i;

    /* Generate two subrooms from a high-width room */
    if(horizontal) {
        int y;
        /* Generate a separating wall */
        for(y=l_i; y <= l_j; y++) {
            (terrain->tiles)[L_div][y] = WALL;
        }
        /* Generate openings */
        for(y=0; y < DOOR_WIDTH; y++) {
            (terrain->tiles)[L_div][anchor+y] = MANA;
        }
        make_inner_walls(terrain, L_i, l_i, L_div - 1, l_j);
        make_inner_walls(terrain, L_div + 1, l_i, L_j, l_j);
    }

    /* Generate two subrooms from a high-length room */
    else {
        int x;
        /* Generate a separating wall */
        for(x=l_i; x <= l_j; x++) {
            (terrain->tiles)[x][L_div] = WALL;
        }
        /* Generate openings */
        for(x=0; x < DOOR_WIDTH; x++) {
            (terrain->tiles)[anchor+x][L_div] = MANA;
        }
        make_inner_walls(terrain, l_i, L_i, l_j, L_div - 1);
        make_inner_walls(terrain, l_i, L_div + 1, l_j, L_j);
    }
}

int terminate_room_generation(Terrain* terrain, int x_i, int y_i, int x_j, int y_j) {
    int i,j;
    for(i=x_i;i<=x_j;i++) {
        for(j=y_i;j<=y_j;j++) {
            if(euclidian_distance(2,2,i,j)>MIN_RELIC_SPAWN_DISTANCE+1) {
                (terrain->tiles)[i][j] = RELIC_CANDIDATE;
            }
        }
    }
    return 0;
}

/**
 * @brief Checks whether the room generation algorithm terminantes and determines the current room's longest side.
 * 
 * @param terrain 
 * @param x_i 
 * @param y_i 
 * @param x_j 
 * @param y_j 
 * @return int 
 */
int make_inner_walls(Terrain* terrain, int x_i, int y_i, int x_j, int y_j) {
    int room_width = x_j - x_i;
    int room_height = y_j - y_i;
    int side = max(room_width, room_height)+1;
    int horizontal = room_width > room_height;

    /* Check the algorithm termination */
    if(side < 2 * MINSIDE + 1) {
        terminate_room_generation(terrain,x_i,y_i,x_j,y_j);
        return 0;
    }
    if(side < 4 * MINSIDE && random_seed() < 0.5) {
        terminate_room_generation(terrain,x_i,y_i,x_j,y_j);
        return 0;
    }
    
    /* Generate two subrooms from a high-width room */
    if(horizontal) {
        cut_along_max_length(terrain, x_i, y_i, x_j, y_j, 1);
    }
    /* Generate two subrooms from a high-height room */
    else {
        cut_along_max_length(terrain, y_i, x_i, y_j, x_j, 0);
    }
    return 0;
}

/**
 * @brief Generates relics at random place available.
 * 
 * @param terrain 
 * @return int 
 */
int generate_relics(Terrain* terrain) {
    int p, i, j;
    /* Place relics */
    for(p=0;p<RELIC_NUMBER;p++) {
        int x = L3_randint(1,TERRAIN_WIDTH-2);
        int y = L3_randint(1,TERRAIN_HEIGHT-2);
        while((terrain->tiles)[x][y]!=RELIC_CANDIDATE) {
            x = L3_randint(1,TERRAIN_WIDTH-2);
            y = L3_randint(1,TERRAIN_HEIGHT-2);  
        }
        (terrain->tiles)[x][y] = RELIC;
    }

    /* Clear all relic candidate tiles */
    for(i=1;i<TERRAIN_WIDTH-1;i++) {
        for(j=1;j<TERRAIN_HEIGHT-1;j++) {
            if((terrain->tiles)[i][j]==RELIC_CANDIDATE) {
                (terrain->tiles)[i][j]=MANA;
            }
        }
    }    
    return 0;
}

/**
 * @brief Generates the number of mana given at random place available.
 * 
 * @param terrain 
 * @param nb_mana 
 * @return int 
 */
int generate_mana(Terrain* terrain, int nb_mana) {
    int i;
    Coords coords;
    /* Place mana */
    for(i = 0; i < nb_mana; i++) {
        pop_random(&coords,&(terrain->collected_mana));
        (terrain->tiles)[coords.i][coords.j] = MANA;
    }
    return 0;
}

/**
 * @brief Generates the playground's inner walls.
 * 
 * @param terrain 
 * @return int 
 */
int generate_terrain(Terrain *terrain) {
    /* Generate outer walls */
    int i,j;
    for(i=0;i<TERRAIN_WIDTH;i++) {
        (terrain->tiles)[i][0] = WALL;
        (terrain->tiles)[i][TERRAIN_HEIGHT-1] = WALL;
    }
    for(j=0;j<TERRAIN_HEIGHT;j++) {
        (terrain->tiles)[0][j] = WALL;
        (terrain->tiles)[TERRAIN_WIDTH-1][j] = WALL;
    }

    /* Generate game field */
    for(i=1;i<TERRAIN_WIDTH-1;i++) {
        for(j=1;j<TERRAIN_HEIGHT-1;j++) {
            if((i==1||i==2)&&(j==1||j==2)) {
                (terrain->tiles)[i][j] = ENTRANCE;
            }
            else {
                (terrain->tiles)[i][j] = MANA;
            }
        }
    }
    
    /* Room generation */
    make_inner_walls(terrain, 1, 1, TERRAIN_WIDTH - 2, TERRAIN_HEIGHT - 2);

    /* Fill all relic candidates with mana. */
    generate_relics(terrain);

    return 0;
}

/**
 * @brief Checks whether a point p(x_p,y_p) can be spotted from a point g(x_g,y_g) in terrrain t.
 * 
 * @param p 
 * @param g 
 * @param t
 * @return int 
 */
int point_spotted(float x_g, float y_g, float x_p, float y_p, Terrain* t) {
    int x0 = min((int)x_g,(int)x_p);
    int y0 = min((int)y_g,(int)y_p);
    int x1 = max((int)x_g,(int)x_p);
    int y1 = max((int)y_g,(int)y_p);
    float theta;
    int xB,yB;
    int x,y;
    /* Lines */
    if(x0!=x1) {
        for(x=x0+1;x<=x1;x++) {
            theta = ((float)x-x_g)/(x_p-x_g);
            if(theta>1||theta<0) {
            }
            yB = (int) (y_p*theta + y_g*(1-theta));
            if(t->tiles[x-1][yB]==WALL||t->tiles[x][yB]==WALL) {
                return 0;
            }
        }
    }
    /* Columns */
    if(y0!=y1) {
        for(y=y0+1;y<=y1;y++) {
            theta = ((float)y-y_g)/(y_p-y_g);
            if(theta>1||theta<0) {
            }
            xB = (int) (x_p*theta + x_g*(1-theta));
            if(t->tiles[xB][y-1]==WALL||t->tiles[xB][y]==WALL) {
                return 0;
            }
        }
    }
    return 1;
}