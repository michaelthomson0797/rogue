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
#define WALL    '#'
#define DOOR    '+'
#define EMPTY   ' '

/*
 * grid parameters
 */
#define WIDTH   50
#define HEIGHT  25


/*
 * coordinate structure
 */
typedef struct coord {
    int x;
    int y;
} coord;

/*
 * structure to represent creatures
 */
typedef struct Creature
{
    char type;
    coord c_pos;
} Creature;


/*
 * structure for the grid of creatures
 */
typedef struct CreatureGrid
{
    int height;
    int width;
    Creature*** grid;
} CreatureGrid;

/*
 * structure for tiles on the mapgrid
 */
typedef struct Tile
{
    char type;
    coord t_pos;
    int passable;
    int playerPresent;
} Tile;

/*
 * structure to hold the map grid
 */
typedef struct MapGrid
{
    int height;
    int width;
    Tile*** grid;
} MapGrid;



/*
 * functions
 */
MapGrid* mkMapGrid(char filename[]);
void printMapGrid(MapGrid* map);

Tile* mkFloor(int x, int y);
Tile* mkWall(int x, int y);
Tile* mkEmpty(int x, int y);

CreatureGrid* mkCreatureGrid();
void printCreatureGrid(CreatureGrid* creaturegrid);
