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

// room methods
Room *mkRoom(int lx, int ly, int rx, int ry, int width, int height);
int isIntersecting(Room *room1, Room *room2);
int getCenterX(Room *room);
int getCenterY(Room *room);

// roomnode methods
RoomNode *mkRoomNode(Room *room);
void appendRoom(Room *room, RoomNode* roomNode);

// Action methods
Action *mkAction(int type, Actor *actor, int x, int y);
void performAction(Action *action);
