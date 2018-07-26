#include "global.h"

/*
 * Creates a MapGrid pointer from a level text file
 */
MapGrid* mkMapGrid(char filename[]) {
    MapGrid* map = (MapGrid*) malloc(sizeof(MapGrid));

    map->height = HEIGHT;
    map->width = WIDTH;


    map->grid = (Tile***) malloc(map->width * sizeof(Tile**));

    for(int i = 0; i < map->width+1; i++) {
        map->grid[i] = (Tile**) malloc(map->height * sizeof(Tile*));
    }

    FILE* file = fopen(filename, "r");
    for(int y = 0; y < map->height; y++) {
        for(int x = 0; x <= map->width; x++) {
            char ch = getc(file);

            if(ch == '\n') continue;

            switch(ch) {
                case '.':
                    map->grid[x][y] = mkFloor(x, y);
                    break;
                case '#':
                    map->grid[x][y] = mkWall(x, y);
                    break;
                default:
                    map->grid[x][y] = mkEmpty(x, y);
                    break;
            }
        }
    }
    return map;
}

/*
 * clears the screen then prints the map onto the standard window
 * TODO: move player info to seperate grid
 */
void printMapGrid(MapGrid* map) {
   for(int y = 0; y < map->height; y++) {
       for(int x = 0; x < map->width; x++) {
           mvdelch(y, x);
           if(map->grid[x][y]->playerPresent) {
                mvaddch(y, x, '@');
           } else {
                mvaddch(y, x, map->grid[x][y]->type);
           }
       }
   }
}

