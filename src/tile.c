#include "global.h"

// Constructor for making a tile given inputs
Tile *mkGenericTile(int type, char appearance, int passable, int explored,
             int visible, Actor *actor, int x, int y)
{
  Tile *tile = malloc(sizeof(Tile));
  tile->type = type;
  tile->appearance = appearance;
  tile->passable = passable;
  tile->explored = explored;
  tile->visible = visible;
  tile->actor = actor;
  tile->x = x;
  tile->y = y;

  return tile;
}

// abstracted tile creation. takes a type and creates the tile
Tile *mkTile(int type, int x, int y)
{
  switch (type)
  {
  case WALL:
    return mkGenericTile(WALL, '#', 0, 0, 0, NULL, x, y);
  
  case FLOOR:
    return mkGenericTile(FLOOR, '.', 1, 0, 0, NULL, x, y);
  
  case EMPTY:
    return mkGenericTile(EMPTY, ' ', 0, 0, 0, NULL, x, y);
    
  default:
    return mkGenericTile(EMPTY, ' ', 0, 0, 0, NULL, x, y);
  }
}

// given a pointer to a tile, this will get the appearance
char getAppearance(Tile *tile) {
  return tile->actor == NULL ? tile->appearance : tile->actor->appearance;
}