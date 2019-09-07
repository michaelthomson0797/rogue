#include "global.h"

Room *mkRoom(int lx, int ly, int rx, int ry, int width, int height)
{
  Room *room = malloc(sizeof(Room));
  room->lx = lx;
  room->ly = ly;
  room->rx = rx;
  room->ry = ry;
  room->width = width;
  room->height = height;
  return room;
}

int isIntersecting(Room *room1, Room *room2)
{
  if (room1->lx > room2->rx || room2->lx > room1->rx)
    return 0;
  
  if (room1->ly > room2->ry || room2->ly > room1->ry)
    return 0;

  return 1;
}
