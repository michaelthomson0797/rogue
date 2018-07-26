#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tiles.c"

struct MapGrid
{
    int height;
    int width;
    struct Tile*** grid;
};

struct MapGrid* mkMapGrid(char filename[]) {
    struct MapGrid* map = (struct MapGrid*) malloc(sizeof(struct MapGrid));

    map->height = 25;
    map->width = 50;


    map->grid = (struct Tile***) malloc(map->width * sizeof(struct Tile**));

    for(int i = 0; i < map->width+1; i++) {
        map->grid[i] = (struct Tile**) malloc(map->height * sizeof(struct Tile*));
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

char** getMapGridString(struct MapGrid* map){
    char** string = (char**) malloc(map->width * sizeof(char*));

    for(int x = 0; x < map->width; x++) {
        string[x] = (char*) malloc(map->height * sizeof(char));
        for(int y = 0; y < map->height; y++) {
            if(map->grid[x][y]->playerPresent) {
                string[x][y] = '@';
            } else {
                string[x][y] = map->grid[x][y]->str;
            }
        }
    }

    return string;
}

void printMapGrid(struct MapGrid* map) {
   char** mapstring = getMapGridString(map);

   for(int y = 0; y < map->height; y++) {
       for(int x = 0; x < map->width; x++) {
           mvdelch(y, x);
           mvaddch(y, x, mapstring[x][y]);
       }
   }
}

