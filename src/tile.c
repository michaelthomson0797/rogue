#include "global.h"

/*
 * initializes and returns a pointer to a new Tile
 */
Tile *mkTile(int x, int y)
{
    Tile *tile = (Tile *)malloc(sizeof(Tile));
    tile->pos.x = x;
    tile->pos.y = y;
    tile = mkWall(x, y);
    tile->creature = NULL;
    tile->seen = 0;
    tile->visible = 0;
    return tile;
}

/*
 * checks whether a Tile is currently passable by a creature
 */
int isPassable(Tile *tile)
{
    return tile->passable && tile->creature == NULL;
}
