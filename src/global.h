/*
 * global definitions and variable declarations
 */

/*
 * library inclusions
 */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>


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
#define WIDTH           200
#define HEIGHT          200
#define MAX_ROOMS       100
#define MIN_ROOM_SIZE   5
#define MAX_ROOM_SIZE   12


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
 * structure to hold a room's info
 */
typedef struct Room
{
    coord r_pos1;
    coord r_pos2;
    int height;
    int width;
    coord center;
} Room;

/*
 * structure to hold the map grid
 */
typedef struct MapGrid
{
    int height;
    int width;
    Creature* player;
    Tile*** grid;
    Room** rooms;
} MapGrid;


/*
 * functions
 */
MapGrid* mkMapGrid(char filename[]);
void printMapGrid(MapGrid* map);

Room*  mkRoom(int x, int y, int h, int w);
void addRoom(Room* room, MapGrid* mapgrid);
int intersect(Room* room1, Room* room2);
coord center(Room* room);

Tile* mkFloor(int x, int y);
Tile* mkWall(int x, int y);
Tile* mkEmpty(int x, int y);

CreatureGrid* mkCreatureGrid();
void printCreatureGrid(CreatureGrid* creaturegrid);

Creature* mkCreature(char type, int x, int y);
