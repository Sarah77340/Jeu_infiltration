/* CROZAT Alex
NGUYEN Sarah
Entity handling module
*/

#include "../include/entity.h"

/**
* @brief Allocates memory for entity
*/
Entity * init_entity(Type type){
    Entity * e = (Entity*)malloc(sizeof(Entity));
    if (e == NULL){
        fprintf(stderr, "erreur allocation sur p\n");
        return NULL;
    }
    switch (type){
        case PLAYER:
            e->x = 2;
            e->y = 2;
            e->speed = SPEED * PLAYER_MIN_SPEED;
            e->direction = EAST;
            break;
        case GUARDIAN:
            e->x = L3_randint(1,TERRAIN_WIDTH-2)+0.5;
            e->y = L3_randint(1,TERRAIN_HEIGHT-2)+0.5;
            e->speed = SPEED * L3_random(GUARDIAN_MIN_SPEED,GUARDIAN_MAX_SPEED);
            e->direction = L3_randint(0,3);
            break;
        case PANIC_GUARDIAN:
            e->x = L3_randint(1,TERRAIN_WIDTH-2)+0.5;
            e->y = L3_randint(1,TERRAIN_HEIGHT-2)+0.5;
            e->speed = SPEED * PANIC_GUARDIAN_SPEED;
            e->direction = L3_randint(0,3);
            break;        
    }
    e->r = 0.5;
    /*e->direction = L3_randint(0,3);*/
    e->type = type;
    return e;
}

int update_entity_position(Entity* e, Point p_col) {
    float x_next, y_next;
    int x_dir[4] = {0,0,1,-1};
    int y_dir[4] = {-1,1,0,0};
    
    x_next = e->x + e->speed * x_dir[e->direction] * 1 / STEPS;
    y_next = e->y + e->speed * y_dir[e->direction] * 1 / STEPS;
    /* Ensure that the entity does not collide with a wall */
    if((x_next-p_col.x)*(e->x-p_col.x)<=0) {
        e->x = p_col.x;
    } else {
        e->x = x_next;
    }
    if((y_next-p_col.y)*(e->y-p_col.y)<=0) {
        e->y = p_col.y;
    } else {
        e->y = y_next;
    }
    return 0;
}


/**
 * @brief Checks whether entity e collides with point p_col
 * 
 * @param e 
 * @param p_col 
 * @return int 
 */
int check_collision(Entity* e, Point p_col) {
    return(e->x==p_col.x||e->y==p_col.y);
}

/**
 * @brief Handles entity collisions with walls by correcting entity position.
 * Returns the coordinates of the next not crossable point, or (0,0) if there are no movement constraints.
 * 
 * @param t 
 * @param e 
 */
Point collision_bound(Terrain* t, Entity* e) {
    Point p_col = {0.0,0.0};
    int x_dir[4] = {0,0,1,-1};
    int y_dir[4] = {-1,1,0,0};
    int x_var = x_dir[e->direction];
    int y_var = y_dir[e->direction];
    int i = (int)e->x;
    int j = (int)e->y;
    int i_col = i + x_var;
    int j_col = j + y_var;
    float delta_x=0, delta_y=0;

    /* Normal collisions */
    if((t->tiles)[i_col][j_col]==WALL) {
        delta_x = max(0,x_var) - e->r * x_var;
        delta_y = max(0,y_var) - e->r * y_var;
        if(e->type==PLAYER) {
            printf("%d %d\n",max(0,x_var),max(0,y_var));
        }
    }

    

    else {
        /* Angular collisions */
        int x_ortho = abs(y_var);
        int y_ortho = abs(x_var);
        int kaki = 0;
        int kakj = 0;
        /* Negative case : the wall is in the negative direction orthogonal to the move cardinal direction */
        if((t->tiles)[i_col-x_ortho][j_col-y_ortho]==WALL) {
            kakj = max(e->r * e->r - (e->y - j)*(e->y - j),kakj);
            kaki = max(e->r * e->r - (e->x - i)*(e->x - i),kaki);
        }
        /* Positive case : the wall is in the positive direction orthogonal to the move cardinal direction */
        if((t->tiles)[i_col+x_ortho][j_col+y_ortho]==WALL) {
            kakj = max(e->r * e->r - (e->y - (j+y_ortho))*(e->y - (j+y_ortho)),kakj);
            kaki = max(e->r * e->r - (e->x - (i+x_ortho))*(e->x - (i+x_ortho)),kaki);
        }
        if(kaki!=0) {
            delta_x = max(0,x_var) - sqrt( kakj ) * x_var;
        }
        if(kakj!=0) {
            delta_y = max(0,y_var) - sqrt( kaki ) * y_var;
        }
    }

    /* Set limit position if a collision occured */
    if(delta_x!=0||delta_y!=0) {
        if(delta_x!=0) {
            p_col.x = i + delta_x;
        }
        if(delta_y!=0) {
            p_col.y = j + delta_y;
        }
    }
    return p_col;
}



int place_guardian(Terrain* board, Entity* e) {
    if(e->type!=GUARDIAN) {
        return 1;
    }
    e->x = L3_randint(1,TERRAIN_WIDTH-2);
    e->y = L3_randint(1,TERRAIN_HEIGHT-2);
    while((board->tiles)[(int)e->x][(int)e->y]==WALL || euclidian_distance(2,2,e->x,e->y)<=MIN_GUARDIAN_SPAWN_RANGE) {
        e->x = L3_randint(1,TERRAIN_WIDTH-2);
        e->y = L3_randint(1,TERRAIN_HEIGHT-2);        
    }
    e->x += 0.5;
    e->y += 0.5;
    return 0;
}

int change_guardian_trajectory(Entity* e) {
    if(e->type != GUARDIAN && e->type != PANIC_GUARDIAN) {
        return 1;
    }
    if(e->type==GUARDIAN) {
        e->speed = SPEED * L3_random(GUARDIAN_MIN_SPEED,GUARDIAN_MAX_SPEED);
    }
    e->direction = L3_randint(0,3);
    return 0;
}

int move_normal_guardian(Entity* e, Point p_col) {
    if(e->type != GUARDIAN) {
        return 1;
    }
    update_entity_position(e, p_col);
    if(random_seed()<GUARDIAN_TURNS||check_collision(e,p_col)) {
        change_guardian_trajectory(e);
    }
    return 0;
}

int move_panic_guardian(Entity* e, Point p_col) {
    if(e->type != PANIC_GUARDIAN) {
        return 1;
    }
    update_entity_position(e, p_col);
    /* If panic_guardian sees a wall within a 1-tile radius, he rotates too.*/
    if(random_seed()<GUARDIAN_TURNS||check_collision(e,p_col)) {
        change_guardian_trajectory(e);
    }
    return 0;
}