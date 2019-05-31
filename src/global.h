#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

// Map Dimensions
#define HEIGHT 15
#define WIDTH 50


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
  ATTACK
};

// structure declarations
typedef struct Actor Actor;
typedef struct actorNode actorNode;
typedef struct Tile Tile;
typedef struct Map Map;
typedef struct Game Game;
typedef struct Action Action;

// global variables
Map* map;

// Actor types
enum actorTypes
{
  PLAYER,
  MONSTER
};

// Actor Structure
struct Actor
{
  int type;
  char appearance;
  int energy;
  int speed;
  int x, y;
};

struct actorNode
{
  Actor *actor;
  actorNode *next;
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
};

// Game Structure
struct Game
{
  actorNode *currentActorNode;
  actorNode *actorHead;
};

// Action structure
struct Action
{
  int type;
  Actor *actor;
  int x;
  int y;
};


// Method Signatures
// Actor methods
Actor *mkActor(int type, int x, int y);
Action *getAction(Actor *actor);

// Tile methods
Tile *mkTile(int type, int x, int y);
char getAppearance(Tile *tile);

// Display methods
void initDisplay();
void render(Map *map);

// game methods
void run(Game *game);

// map methods
Map *mkMap();

// Action methods
Action *mkAction(int type, Actor *actor, int x, int y);
void performAction(Action *action);