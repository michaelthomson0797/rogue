#include "global.h"

MapGrid* mkMapGrid(char filename[]) {
    MapGrid* map = (MapGrid*) malloc(sizeof(MapGrid));

    map->height = 25;
    map->width = 50;


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

char** getMapGridString(MapGrid* map){
    char** string = (char**) malloc(map->width * sizeof(char*));

    for(int x = 0; x < map->width; x++) {
        string[x] = (char*) malloc(map->height * sizeof(char));
        for(int y = 0; y < map->height; y++) {
            if(map->grid[x][y]->playerPresent) {
                string[x][y] = '@';
            } else {
                string[x][y] = map->grid[x][y]->type;
            }
        }
    }

    return string;
}

void printMapGrid(MapGrid* map) {
   char** mapstring = getMapGridString(map);

   for(int y = 0; y < map->height; y++) {
       for(int x = 0; x < map->width; x++) {
           mvdelch(y, x);
           mvaddch(y, x, mapstring[x][y]);
       }
   }
}

