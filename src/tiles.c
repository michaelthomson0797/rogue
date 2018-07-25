struct Tile
{
    char str;
    int xpos, ypos;
    int passable;
    int playerPresent;
};

struct Tile* mkFloor(int x, int y) {
    struct Tile* tile = (struct Tile*) malloc(sizeof(struct Tile));
    tile->str = '.';
    tile->xpos = x;
    tile->ypos = y;
    tile->passable = 1;
    tile->playerPresent = 0;
    return tile;
}

struct Tile* mkWall(int x, int y) {
    struct Tile* tile = (struct Tile*) malloc(sizeof(struct Tile));
    tile->str = '#';
    tile->xpos = x;
    tile->ypos = y;
    tile->passable = 0;
    tile->playerPresent = 0;
    return tile;
}

struct Tile* mkEmpty(int x, int y) {
    struct Tile* tile = (struct Tile*) malloc(sizeof(struct Tile));
    tile->str = ' ';
    tile->xpos = x;
    tile->ypos = y;
    tile->passable = 0;
    tile->playerPresent = 0;
    return tile;
}
