#include "global.h"

Cell* mkCell(int x, int y) {
    Cell* cell = (Cell*) malloc(sizeof(Cell));
    cell->c_pos.x = x;
    cell->c_pos.y = y;
    cell->tile = mkEmpty(x, y);
    cell->creature = NULL;
    cell->seen = 0;
    cell->visible = 0;
    return cell;
}

int isPassable(Cell* cell) {
    return cell->tile->passable && cell->creature == NULL;
}
