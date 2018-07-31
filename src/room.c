#include "global.h"

/*
 * initialize and return a pointer to a Room
 */
Room* mkRoom(int x, int y, int h, int w) {
    Room* room = (Room*) malloc(sizeof(Room));
    room->r_pos1.x = x;
    room->r_pos1.y = y;
    room->r_pos2.x = x + w;
    room->r_pos2.y = y + h;
    room->height = h;
    room->width = w;
    room->center = center(room);

    return room;
}

/*
 * adds a room to the mapgrid
 */
void addRoom(Room* room, MapGrid* mapgrid) {
    for(int x = room->r_pos1.x; x <= room->r_pos2.x; x++) {
        for(int y = room->r_pos1.y; y <= room->r_pos2.y; y++) {
            if (x == room->r_pos1.x || y == room->r_pos1.y || x == room->r_pos2.x || y == room->r_pos2.y) {
                mapgrid->grid[x][y]->tile = mkWall(x, y); 
            } else {
                mapgrid->grid[x][y]->tile = mkFloor(x, y); 
            }   
        }   
    }   
}

/*
 * creates a horizontal tunnel and adds it to the mapgrid
 */
void addTunnelH(MapGrid* mapgrid, int x1, int x2, int y) {
    int xmax = max(x1, x2);
    int xmin = min(x1, x2);
    for(int x = xmin; x <= xmax; x++) {
        mapgrid->grid[x][y]->tile = mkFloor(x, y);
    }
}

/*
 * creates a vertical tunnela and adds it to the mapgrid
 */
void addTunnelV(MapGrid* mapgrid,int y1, int y2, int x) {
    int ymax = max(y1, y2);
    int ymin = min(y1, y2);
    for(int y = ymin; y <= ymax; y++) {
        mapgrid->grid[x][y]->tile = mkFloor(x, y);
    }
}

/*
 * calculates the center of a Room and returns a coordinate
 */
coord center(Room* room) {
    coord Coord;
    
    Coord.x = room->r_pos1.x + room->width/2;
    Coord.y = room->r_pos1.y + room->height/2;

    return Coord;
}

/*
 * checks if two rooms are intersecting. returns 1 if they intersect, 0 otherwise
 */
int intersect(Room* room1, Room* room2) {
   if(room1->r_pos1.x <= room2->r_pos2.x && room1->r_pos2.x >= room2->r_pos1.x &&
        room1->r_pos1.y <= room2->r_pos2.y && room1->r_pos2.y >= room2->r_pos1.y) {
       return 1;
   }
   return 0;
}
/*
 * checks if a coordinate is inside a room
 */
int inRoom(Room* room, int x, int y) {
    if (room->r_pos1.x <= x && room->r_pos1.y <= y && room->r_pos2.x >= x && room->r_pos2.y >= y) {
        return 1;
    }
    return 0;
}
