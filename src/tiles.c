#include "global.h"

Tile* mkFloor(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = FLOOR;
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 1;
    return tile;
}

Tile* mkWall(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = WALL;
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 0;
    return tile;
}

Tile* mkEmpty(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = EMPTY;
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 0;
    return tile;
}
