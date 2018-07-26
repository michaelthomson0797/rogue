#include "global.h"

Creature* mkCreature(char type, int x, int y) {
    Creature* creature = (Creature*) malloc(sizeof(Creature));
    creature->type = type;
    creature->c_pos.x = x;
    creature->c_pos.y = y;
    return creature;
}
