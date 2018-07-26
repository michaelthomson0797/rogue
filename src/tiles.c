#include "global.h"

Tile* mkFloor(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = '.';
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 1;
    tile->playerPresent = 0;
    return tile;
}

Tile* mkWall(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = '#';
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 0;
    tile->playerPresent = 0;
    return tile;
}

Tile* mkEmpty(int x, int y) {
    Tile* tile = (Tile*) malloc(sizeof(Tile));
    tile->type = ' ';
    tile->t_pos.x = x;
    tile->t_pos.y = y;
    tile->passable = 0;
    tile->playerPresent = 0;
    return tile;
}
