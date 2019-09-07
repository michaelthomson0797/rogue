#include "global.h"

Map *mkMap() {

  map = malloc(sizeof(Map));

  map->height = HEIGHT;
  map->width = WIDTH;


  //initialize rooms to empty
  for(int y = 0; y < HEIGHT; y++) {
    for(int x = 0; x < WIDTH; x++) {
      map->grid[y][x] = mkTile(EMPTY, x, y);
    }
  }

  Room *room = generateRandomRoom();
  map->roomHead = mkRoomNode(room);
  placeRoom(map->roomHead->room);

  for(int i = 0; i < ROOMPLACEMENTS; i++) {
    // create random room in bounds of map
    room = generateRandomRoom();

    // see if the room fits
    if(doesRoomFit(room, map->roomHead)) {
      placeRoom(room);
      appendRoom(room, map->roomHead);
    }
  }

  placeTunnels();
  
  return map;
}

Room *generateRandomRoom()
{
  int width = (rand() % (MAXROOMWIDTH - MINROOMWIDTH + 1)) + MINROOMWIDTH;
  int height = (rand() % (MAXROOMHEIGHT - MINROOMHEIGHT + 1)) + MINROOMHEIGHT;

  int lx = (rand() % (WIDTH - width - 0 + 1)) + 0;
  int ly = (rand() % (HEIGHT - height - 0 + 1)) + 0;

  Room *room = mkRoom(lx, ly, lx+width, ly+height, width, height);
  return room;
}

int doesRoomFit(Room *roomToCheck, RoomNode *roomHead)
{
  for(RoomNode *currRoomNode = roomHead; currRoomNode != NULL; currRoomNode = currRoomNode->next){
    if(isIntersecting(roomToCheck, currRoomNode->room)){
      return 0;
    }
  }

  return 1;
}

void placeRoom(Room *room)
{
  for(int y = room->ly; y < room->ly + room->height; y++) {
    for(int x = room->lx; x < room->lx + room->width; x++) {
      // walls
      if (x == room->lx || x == room->lx + room->width - 1 ||
          y == room->ly || y == room->ly + room->height - 1) {
        map->grid[y][x] = mkTile(WALL, x, y);
      } else {
        map->grid[y][x] = mkTile(FLOOR, x, y);
      }
    }
  }
}

void placeTunnels()
{
  // loop through all rooms
  for(RoomNode *currRoomNode = map->roomHead; currRoomNode->next != NULL; currRoomNode = currRoomNode->next){
    // get source and target coordinates
    int sx = getCenterX(currRoomNode->room);
    int sy = getCenterY(currRoomNode->room);
    int tx = getCenterX(currRoomNode->next->room);
    int ty = getCenterY(currRoomNode->next->room);

    // vertical or horizontal first?
    int VorH = rand()%2;

    if(VorH) {
      //vertical first
      placeVerticalTunnel(sy, ty, sx);
      placeHorizontalTunnel(sx, tx, ty);
    } else {
      // horizontal first
      placeHorizontalTunnel(sx, tx, sy);
      placeVerticalTunnel(sy, ty, tx);
    } 
  }
}

void placeVerticalTunnel(int sy, int ty, int x) {
  if (sy < ty) {
    for(int y = sy; y <= ty; y++) {
      map->grid[y][x] = mkTile(FLOOR, x, y);
    }
  } else {
    for(int y = ty; y <= sy; y++) {
      map->grid[y][x] = mkTile(FLOOR, x, y);
    }
  }
}

void placeHorizontalTunnel(int sx, int tx, int y) {
  if (sx < tx) {
    for(int x = sx; x <= tx; x++) {
      map->grid[y][x] = mkTile(FLOOR, x, y);
    }
  } else {
    for(int x = tx; x <= sx; x++) {
      map->grid[y][x] = mkTile(FLOOR, x, y);
    }
  }
}
