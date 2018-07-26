/*
 * global definitions and variable declarations
 */

/*
 * library inclusions
 */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


/*
 * displayable items
 */
#define FLOOR   '.'
#define WALL    '#';
#define DOOR    '+';


/*
 * coordinate structure
 */
typedef struct coord {
    int x;
    int y;
} coord;

/*
 * structure to hold the map grid
 */
typedef struct MapGrid
{
    int height;
    int width;
    struct Tile*** grid;
} MapGrid;

typedef struct Tile
{
    char type;
    coord t_pos;
    int passable;
    int playerPresent;
} Tile;



/*
 * functions
 */
MapGrid* mkMapGrid(char filename[]);
char** getMapGridString(MapGrid* map);
void printMapGrid(MapGrid* map);

Tile* mkFloor(int x, int y);
Tile* mkWall(int x, int y);
Tile* mkEmpty(int x, int y);
