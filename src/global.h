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
#include <stdbool.h>

/*
 * useful functions
 */
#define max(x, y) ((x) >= (y)) ? (x) : (y)
#define min(x, y) ((x) <= (y)) ? (x) : (y)

/*
 * displayable items
 */
#define FLOOR '.'
#define WALL '#'
#define DOOR '+'
#define EMPTY ' '

/*
 * grid parameters
 */
#define WIDTH 50
#define HEIGHT 40
#define MAX_ROOMS 10
#define MIN_ROOM_SIZE 5
#define MAX_ROOM_SIZE 12

/*
 * coordinate structure
 */
typedef struct coord
{
    int x;
    int y;
} coord;

/*
 * structure to represent creatures
 */
typedef struct Creature
{
    char type;
    coord pos;
} Creature;

/*
 * structure for tiles on the mapgrid
 */
typedef struct Tile
{
    coord pos;
    char type;
    bool passable;
    int seen;
    int visible;

    Creature *creature;

} Tile;

/*
 * structure to hold a room's info
 */
typedef struct Room
{
    coord pos1;
    coord pos2;
    int height;
    int width;
    coord center;
} Room;

/*
 * structure to hold the map grid */
typedef struct MapGrid
{
    int height;
    int width;
    Creature *player;
    Tile *grid[WIDTH][HEIGHT];
    int num_rooms;
    Room *rooms[MAX_ROOMS];
} MapGrid;

/*
 * functions
 */
MapGrid *mkMapGrid();
void updateVisibility(MapGrid *map);
void printMapGrid(MapGrid *map);

Tile *mkTile(int x, int y);
int isPassable(Tile *tile);

Room *mkRoom(int x, int y, int h, int w);
void addRoom(MapGrid *mapgrid, Room *room);
void addTunnelH(MapGrid *mapgrid, int x1, int x2, int y);
void addTunnelV(MapGrid *mapgrid, int y1, int y2, int x);
bool intersect(Room *room1, Room *room2);
coord center(Room *room);
int inRoom(Room *room, int x, int y);

Tile *mkFloor(int x, int y);
Tile *mkWall(int x, int y);
Tile *mkEmpty(int x, int y);

Creature *mkCreature(char type, int x, int y);
void mvCreature(MapGrid *mapgrid, Creature *creature, int x, int y);
