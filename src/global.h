#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include "AStar.h"

// Map properties
#define HEIGHT 20
#define WIDTH 60
#define ROOMPLACEMENTS 5
#define WIDTH_RATIO 0.75
#define HEIGHT_RATIO 0.25
#define BSP_DEPTH 3

// debug
#define PRINT_CONTAINERS 0

// Room properties
#define MINROOMWIDTH 5
#define MAXROOMWIDTH 10

#define MINROOMHEIGHT 4
#define MAXROOMHEIGHT 6

// cost of action
#define ENERGYCOST 12


//Tile types
enum tileTypes
{
  FLOOR,
  WALL,
  EMPTY
};

// Directions
enum direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

// Actions
enum actionTypes
{
  WALK,
  ATTACK,
  WAIT,
  DIE
};

// structure declarations
typedef struct Actor Actor;
typedef struct ActorNode ActorNode;
typedef struct Tile Tile;
typedef struct Map Map;
typedef struct Game Game;
typedef struct Action Action;
typedef struct Room Room;
typedef struct RoomNode RoomNode;


// global variables
Map *map;
Game *game;
ASPathNodeSource *nodeSource;

// Actor types
enum actorTypes
{
  PLAYER,
  GOBLIN,
  CHEETAH,
  SLUG
};

// Actor Structure
struct Actor
{
  int type;
  char appearance;
  int energy;
  int speed;
  int health;
  int damage;
  int x, y;
};

struct ActorNode
{
  Actor *actor;
  ActorNode *next;
};

// Tile Structure
struct Tile
{
  int type;
  char appearance;
  int passable;
  int explored;
  int visible;
  Actor *actor;
  int x, y;

};

// Map structure
struct Map
{
  int height;
  int width;
  Tile *grid[HEIGHT][WIDTH];
  RoomNode *roomHead;
};

// BSP structure
struct BSPNode
{
  struct Container *container;
  struct BSPNode *lNode;
  struct BSPNode *rNode;
};

// Container structure
struct Container
{
  int x, y;
  int width, height;
};


// Room structure
struct Room
{
  int lx, ly;
  int rx, ry;
  int width, height;
};

struct RoomNode
{
  Room *room;
  RoomNode *next;
};

// Game Structure
struct Game
{
  ActorNode *currentActorNode;
  ActorNode *actorHead;
};

// Action structure
struct Action
{
  int type;
  Actor *actor;
  int x;
  int y;
};

/* Method Signatures */
// Actor methods
Actor *mkActor(int type, int x, int y);
Action *getAction(Actor *actor);

// ActorNode methods
ActorNode *mkActorNode(Actor *actor);
void appendActor(Actor *actor);
void removeActor(Actor *actor);

// Tile methods
Tile *mkTile(int type, int x, int y);
char getAppearance(Tile *tile);

// Display methods
void initDisplay();
void render(Map *map);

// game methods
void run();
void process();
void addActor(int type, int x, int y);
void nextActor();

// map methods
Map *mkMap();
Room *generateRandomRoom();
int doesRoomFit(Room *roomToCheck, RoomNode *roomHead);
void placeRoom(Room *room);
void placeTunnels();
void placeHorizontalTunnel(int sx, int tx, int y);
void placeVerticalTunnel(int sy, int ty, int x);
void showContainers(struct BSPNode *tree);
void placeRooms(struct BSPNode *tree);

// room methods
Room *mkRoom(struct Container *c);
int isIntersecting(Room *room1, Room *room2);
int getCenterX(Room *room);
int getCenterY(Room *room);

// roomnode methods
RoomNode *mkRoomNode(Room *room);
void appendRoom(Room *room);

// Action methods
Action *mkAction(int type, Actor *actor, int x, int y);
void performAction(Action *action);

// container methods
struct Container *mkContainer(int x, int y, int width, int height);
struct BSPNode *mkBSPNode(struct Container *container);
struct BSPNode *splitContainer(struct Container *container, int iter);
int getContainerCenterX(struct Container *container);
int getContainerCenterY(struct Container *container);
