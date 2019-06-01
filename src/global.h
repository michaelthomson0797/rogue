#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include "AStar.h"

// Map Dimensions
#define HEIGHT 31
#define WIDTH 151

#define MAPNAME "testmap2.txt"

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


// Method Signatures
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

// Action methods
Action *mkAction(int type, Actor *actor, int x, int y);
void performAction(Action *action);