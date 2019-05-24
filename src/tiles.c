#include "global.h"

/*
 * Creates and initializes a new tile with floor properties
 */
Tile *mkFloor(int x, int y)
{
    Tile *tile = (Tile *)malloc(sizeof(Tile));
    tile->type = FLOOR;
    tile->pos.x = x;
    tile->pos.y = y;
    tile->passable = 1;
    return tile;
}

/*
 * Creates and initializes a new tile with wall properties
 */
Tile *mkWall(int x, int y)
{
    Tile *tile = (Tile *)malloc(sizeof(Tile));
    tile->type = WALL;
    tile->pos.x = x;
    tile->pos.y = y;
    tile->passable = 0;
    return tile;
}

/*
 * Creates and initializes a new tile with empty properties
 */
Tile *mkEmpty(int x, int y)
{
    Tile *tile = (Tile *)malloc(sizeof(Tile));
    tile->type = EMPTY;
    tile->pos.x = x;
    tile->pos.y = y;
    tile->passable = 0;
    return tile;
}
