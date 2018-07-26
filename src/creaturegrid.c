#include "global.h"

/* 
 * Creates a CreatureGrid pointer
 */
CreatureGrid* mkCreatureGrid() {
    CreatureGrid* creaturegrid = (CreatureGrid*) malloc(sizeof(CreatureGrid));

    creaturegrid->height = HEIGHT;
    creaturegrid->width = WIDTH;

    creaturegrid->grid = (Creature***) malloc(WIDTH * sizeof(Creature***));

    for(int i = 0; i < WIDTH; i++) {
        creaturegrid->grid[i] = (Creature**) malloc(HEIGHT * sizeof(Creature*));
    }

    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            creaturegrid->grid[x][y] = NULL;
        }
    }

    return creaturegrid;
}

/*
 * prints the creature grid layer to the standard window
 */
void printCreatureGrid(CreatureGrid* creaturegrid) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            if(creaturegrid->grid[x][y] != NULL) {
                mvdelch(y,x);
                mvaddch(y, x, creaturegrid->grid[x][y]->type);
            }
        }
    }
}
