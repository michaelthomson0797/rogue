#include "global.h"
#include <math.h>

Room *mkRoom(struct Container *c)
{
  Room *room = malloc(sizeof(Room));
  room->lx = c->x + (rand() % (c->width/3 + 1));
  room->ly = c->y + (rand() % (c->height/3 + 1));
  room->width = c->width - (room->lx - c->x);
  room->height = c->height - (room->ly - c->y);
  room->width -= (rand() % (room->width/3 + 1));
  room->height -= (rand() % (room->height/3 + 1));
  room->rx = room->lx + room->width;
  room->ry = room->ly + room->height;

  if(room->lx == getContainerCenterX(c) || room->ly == getContainerCenterY(c))
    return mkRoom(c);
  
  return room;
}

int getCenterX(Room *room) {
  return room->lx + (room->width/2);
}

int getCenterY(Room *room) {
  return room->ly + (room->height/2);
}

int isInRoom(int x, int y, Room *room) {
  if(x > room->lx && x < room->rx && y > room->ly && y < room->ry)
    return 1;

  return 0;
}
