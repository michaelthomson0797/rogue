#include "global.h"

Map *mkMap() {

  map = malloc(sizeof(Map));

  map->height = HEIGHT;
  map->width = WIDTH;
  map->roomHead = NULL;

  //initialize rooms to empty
  for(int y = 0; y < HEIGHT; y++) {
    for(int x = 0; x < WIDTH; x++) {
      map->grid[y][x] = mkTile(EMPTY, x, y);
    }
  }

  struct Container *mainContainer = mkContainer(0, 0, WIDTH, HEIGHT);
  struct BSPNode *tree = splitContainer(mainContainer, BSP_DEPTH);

  placeRooms(tree);

  placeTunnels(tree);

  if(PRINT_CONTAINERS) {
    showContainers(tree);
  }

  return map;
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

void placeTunnels(struct BSPNode *tree)
{
  if(tree->lNode == NULL || tree->rNode == NULL) {
    return;
  }

  placeTunnels(tree->lNode);
  placeTunnels(tree->rNode);
  
  // get source and target coordinates
  int sx = getContainerCenterX(tree->lNode->container);
  int sy = getContainerCenterY(tree->lNode->container);
  int tx = getContainerCenterX(tree->rNode->container);
  int ty = getContainerCenterY(tree->rNode->container);

  if(sx == tx) {
    placeVerticalTunnel(sy, ty, tx);
  } else {
    placeHorizontalTunnel(sx, tx, sy);
  }
}

void placeVerticalTunnel(int sy, int ty, int x) {
  if (sy < ty) {
    for(int y = sy; y <= ty; y++) {
      map->grid[y][x] = mkTile(FLOOR, x, y);
    }} else {
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

void showContainers(struct BSPNode *tree) {
  for(int y = tree->container->y; y < tree->container->y + tree->container->height; y++) {
    for(int x = tree->container->x; x < tree->container->x + tree->container->width; x++) {
      if (x == tree->container->x || x == tree->container->x + tree->container->width - 1 ||
          y == tree->container->y || y == tree->container->y + tree->container->height - 1) {
        map->grid[y][x] = mkTile(WALL, x, y);
      }
    }
  }

  if(tree->lNode != NULL) {
    showContainers(tree->lNode);
  }

  if(tree->rNode != NULL) {
    showContainers(tree->rNode);
  }
}

void placeRooms(struct BSPNode *tree) {
  Room *room = mkRoom(tree->container);

  if(tree->lNode == NULL || tree->rNode == NULL) {
    placeRoom(room);
    appendRoom(room);
    return;
  }

  placeRooms(tree->lNode);
  placeRooms(tree->rNode);
}

void updateVisibility() {
  Actor *hero = game->actorHead->actor;
  int x = hero->x;
  int y = hero->y;

  //clear visibility
  for(int y = 0; y < HEIGHT; y++) {
    for(int x = 0; x < WIDTH; x++) {
      map->grid[y][x]->visible = 0;
    }
  }

  // player can always see one square away in all directions
  map->grid[y-1][x-1]->visible = 1;
  map->grid[y-1][x]->visible = 1;
  map->grid[y-1][x+1]->visible = 1;
  map->grid[y][x-1]->visible = 1;
  map->grid[y][x]->visible = 1;
  map->grid[y][x+1]->visible = 1;
  map->grid[y+1][x-1]->visible = 1;
  map->grid[y+1][x]->visible = 1;
  map->grid[y+1][x-1]->visible = 1;

  //visible tiles become explored
  map->grid[y-1][x-1]->explored = 1;
  map->grid[y-1][x]->explored = 1;
  map->grid[y-1][x+1]->explored = 1;
  map->grid[y][x-1]->explored = 1;
  map->grid[y][x]->explored = 1;
  map->grid[y][x+1]->explored = 1;
  map->grid[y+1][x-1]->explored = 1;
  map->grid[y+1][x]->explored = 1;
  map->grid[y+1][x-1]->explored = 1;

  // player can see entire rooms
  for(RoomNode *roomNode = map->roomHead; roomNode != NULL; roomNode = roomNode->next) {
    if(isInRoom(x, y, roomNode->room)) {
      makeRoomVisible(roomNode->room);
    }
  }
}

void makeRoomVisible(Room *room) {
  for(int x = room->lx; x < room->rx; x++) {
    for(int y = room->ly; y < room->ry; y++) {
      map->grid[y][x]->visible = 1;
      map->grid[y][x]->explored = 1;
    }
  }
}
