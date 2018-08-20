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
 * useful functions
 */
#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)

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
#define WIDTH           80
#define HEIGHT          50
#define MAX_ROOMS       10
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
    struct Creature* next;
    struct Creature* prev;
    char type;
    coord c_pos;
} Creature;

/*
 * structure for tiles on the mapgrid
 */
typedef struct Tile
{
    char type;
    coord t_pos;
    int passable;
} Tile;

/*
 * structure to hold map elements
 */
typedef struct Cell
{
    coord c_pos;
    int seen;
    int visible;
    Tile* tile;
    Creature* creature;
} Cell;

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
 * structure to hold the map grid */
typedef struct MapGrid
{
    int height;
    int width;
    Creature* player;
    Cell*** grid;
    int num_rooms;
    Room** rooms;
} MapGrid;


/*
 * functions
 */
MapGrid* mkMapGrid();
void updateVisibility(MapGrid* map);
void printMapGrid(MapGrid* map);

Cell* mkCell(int x, int y);
int isPassable(Cell* cell);

Room*  mkRoom(int x, int y, int h, int w);
void addRoom(Room* room, MapGrid* mapgrid);
void addTunnelH(MapGrid* mapgrid, int x1, int x2, int y);
void addTunnelV(MapGrid* mapgrid, int y1, int y2, int x);
int intersect(Room* room1, Room* room2);
coord center(Room* room);
int inRoom(Room* room, int x, int y);

Tile* mkFloor(int x, int y);
Tile* mkWall(int x, int y);
Tile* mkEmpty(int x, int y);

Creature* mkCreature(char type, int x, int y);
void mvCreature(MapGrid* mapgrid, Creature* creature, int x, int y);

Creature* creatureFind(Creature** head, Creature* currentCreature);
int creatureInsert(Creature** head, Creature* currentCreature);
void creatureDelete(Creature** head, Creature* currentCreature);
void printLinkedList(Creature* head);
