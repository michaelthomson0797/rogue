#include "global.h"

/*
 * initialize and return a pointer to a Room
 */
Room *mkRoom(int x, int y, int h, int w)
{
    Room *room = (Room *)malloc(sizeof(Room));
    room->tl.x = x;
    room->tl.y = y;
    room->br.x = x + w;
    room->br.y = y + h;
    room->height = h;
    room->width = w;
    room->center = center(room);

    return room;
}


/*
 * creates a horizontal tunnel and adds it to the mapgrid
 */
void addTunnelH(MapGrid *mapgrid, int x1, int x2, int y)
{
    int xmax = max(x1, x2);
    int xmin = min(x1, x2);
    for (int x = xmin; x <= xmax; x++)
    {
        mapgrid->grid[x][y] = mkFloor(x, y);
    }
}

/*
 * creates a vertical tunnela and adds it to the mapgrid
 */
void addTunnelV(MapGrid *mapgrid, int y1, int y2, int x)
{
    int ymax = max(y1, y2);
    int ymin = min(y1, y2);
    for (int y = ymin; y <= ymax; y++)
    {
        mapgrid->grid[x][y] = mkFloor(x, y);
    }
}

/*
 * calculates the center of a Room and returns a coordinate
 */
coord center(Room *room)
{
    coord Coord;

    Coord.x = room->tl.x + room->width / 2;
    Coord.y = room->tl.y + room->height / 2;

    return Coord;
}

/*
 * checks if two rooms are intersecting. returns 1 if they intersect, 0 otherwise
 */
int intersect(Room *room1, Room *room2)
{
    // if(room1->tl.x < room2->br.x && room1->br.x > room2->tl.x &&
    //    room1->tl.y < room2->br.y && room1->br.y > room2->tl.y)
    // {
    //     return true;
    // }
  
    // return false; 

    if ((room1->tl.x-1 > room2->br.x+1) || (room1->br.x+1 < room2->tl.x-1) ||
        (room1->tl.y-1 > room2->br.y+1) || (room1->br.y+1 < room2->tl.y-1))
    {
        return 0;
    }

    return 1;
}
/*
 * checks if a coordinate is inside a room
 */
int inRoom(Room *room, int x, int y)
{
    if (room->tl.x <= x && room->tl.y <= y && room->br.x >= x && room->br.y >= y)
    {
        return 1;
    }
    return 0;
}
