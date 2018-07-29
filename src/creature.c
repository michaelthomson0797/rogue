#include "global.h"

Creature* mkCreature(char type, int x, int y) {
    Creature* creature = (Creature*) malloc(sizeof(Creature));
    creature->type = type;
    creature->c_pos.x = x;
    creature->c_pos.y = y;
    return creature;
}

void mvCreature(MapGrid* mapgrid, Creature* creature, int x, int y) {
    mapgrid->grid[creature->c_pos.x][creature->c_pos.y]->creature = NULL;
    creature->c_pos.x = x;
    creature->c_pos.y = y;
    mapgrid->grid[creature->c_pos.x][creature->c_pos.y]->creature = creature;
}
