#include "global.h"

Creature* mkCreature(char type, int x, int y) {
    Creature* creature = (Creature*) malloc(sizeof(Creature));
    creature->type = type;
    creature->coord.x = x;
    creature->coord.y = y;
    return creature;
}
