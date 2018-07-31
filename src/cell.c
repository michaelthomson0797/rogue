#include "global.h"

/*
 * initializes and returns a pointer to a new Cell
 */
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

/*
 * checks whether a cell is currently passable by a creature
 */
int isPassable(Cell* cell) {
    return cell->tile->passable && cell->creature == NULL;
}
