#include "global.h"

/*
 * Creates a MapGrid pointer from a level text file
 */
MapGrid *mkMapGrid()
{
    map = (MapGrid *)malloc(sizeof(MapGrid));

    map->height = HEIGHT;
    map->width = WIDTH;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            map->grid[x][y] = mkEmpty(x, y);
        }
    }

    srand(time(NULL));
    map->num_rooms = 0;

    for (int i = 0; i < MAX_ROOMS; i++)
    {
        // get a random width and height up to the maximums
        int w = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
        int h = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;

        // get a random top-left coordinat for the room
        int x = rand() % (WIDTH - w);
        int y = rand() % (HEIGHT - h);

        // create the new room prospect
        Room *new_room = mkRoom(x, y, h, w);

        // look for intersections
        int intersects = 0;
        for (int j = 0; j < map->num_rooms; j++)
        {
            intersects = intersect(new_room, map->rooms[j]);
            if(intersects) break;
        }

        // if there is no intersection, add the room to the mapgrid
        if (intersects == 0)
        {
            addRoom(map, new_room);
            map->num_rooms++;
        }
    }

    // for (int i = 1; i < map->num_rooms; i++)
    // {
    //     int VorH = rand() % 1;

    //     int x1 = map->rooms[i - 1]->center.x;
    //     int y1 = map->rooms[i - 1]->center.y;
    //     int x2 = map->rooms[i]->center.x;
    //     int y2 = map->rooms[i]->center.y;

    //     if (VorH)
    //     {
    //         addTunnelH(map, x1, x2, y1);
    //         addTunnelV(map, y1, y2, x2);
    //     }
    //     else
    //     {
    //         addTunnelV(map, y1, y2, x1);
    //         addTunnelH(map, x1, x2, y2);
    //     }
    // }

    floodFill(2, 2, EMPTY, FLOOR, RIGHT);

    map->grid[map->rooms[1]->center.x][map->rooms[1]->center.y]->creature = mkCreature('T', map->rooms[1]->center.x, map->rooms[1]->center.y);
    map->player = mkCreature('@', map->rooms[0]->center.x, map->rooms[0]->center.y);

    return map;
}

/*
 * adds a room to the mapgrid
 */
void addRoom(MapGrid *mapgrid, Room *room)
{
    mapgrid->rooms[mapgrid->num_rooms] = room;

    for (int x = room->tl.x; x <= room->br.x; x++)
    {
        for (int y = room->tl.y; y <= room->br.y; y++)
        {
            // if(x == room->tl.x || x == room->br.x ||
            //    y == room->tl.y || y == room->br.y)
            // {
            //     mapgrid->grid[x][y] = mkWall(x, y);
            // }
            // else
            // {
            //     mapgrid->grid[x][y] = mkFloor(x, y);
            // }
            mapgrid->grid[x][y] = mkWall(x, y);
        }
    }
}

/*
 * updates what the player has seen and what is currently visible
 */
void updateVisibility(MapGrid *map)
{
    for (int x = 0; x < map->width; x++)
    {
        for (int y = 0; y < map->height; y++)
        {
            //map->grid[x][y]->visible = 0;
            map->grid[x][y]->visible = 1;
            map->grid[x][y]->seen = 1;
        }
    }

    for (int i = 0; i < map->num_rooms; i++)
    {
        if (inRoom(map->rooms[i], map->player->pos.x, map->player->pos.y))
        {
            for (int x = map->rooms[i]->tl.x; x <= map->rooms[i]->br.x; x++)
            {
                for (int y = map->rooms[i]->tl.y; y <= map->rooms[i]->br.y; y++)
                {
                    map->grid[x][y]->visible = 1;
                    map->grid[x][y]->seen = 1;
                }
            }
        }
    }

    map->grid[map->player->pos.x][map->player->pos.y]->seen = 1;
    map->grid[map->player->pos.x][map->player->pos.y]->visible = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y]->seen = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y]->visible = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y]->seen = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y]->visible = 1;
    map->grid[map->player->pos.x][map->player->pos.y + 1]->seen = 1;
    map->grid[map->player->pos.x][map->player->pos.y + 1]->visible = 1;
    map->grid[map->player->pos.x][map->player->pos.y - 1]->seen = 1;
    map->grid[map->player->pos.x][map->player->pos.y - 1]->visible = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y + 1]->seen = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y + 1]->visible = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y + 1]->seen = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y + 1]->visible = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y - 1]->seen = 1;
    map->grid[map->player->pos.x + 1][map->player->pos.y - 1]->visible = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y - 1]->seen = 1;
    map->grid[map->player->pos.x - 1][map->player->pos.y - 1]->visible = 1;
}

void floodFill(int x, int y, char targetType, char replaceType, int direction)
{
    if (targetType == replaceType)
        return;

    if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
        return;

    if (map->grid[x][y]->type != targetType)
        return;

    

    switch (direction)
    {
    case DOWN:
        if(y+1 < HEIGHT - 1 && x-1 >= 0 && x+1 < WIDTH - 1 && 
           map->grid[x][y+1]->type == EMPTY && map->grid[x-1][y]->type == EMPTY && map->grid[x+1][y]->type == EMPTY) {
            map->grid[x][y] = mkFloor(x, y);
            floodFill(x, y + 1, targetType, replaceType, DOWN);
            floodFill(x - 1, y, targetType, replaceType, LEFT);
            floodFill(x + 1, y, targetType, replaceType, RIGHT);
        }
        return;
    case UP:
        if(y-1 >= 0 && x-1 >= 0 && x+1 < WIDTH - 1 && 
           map->grid[x][y-1]->type == EMPTY && map->grid[x-1][y]->type == EMPTY && map->grid[x+1][y]->type == EMPTY) {
            map->grid[x][y] = mkFloor(x, y);
            floodFill(x, y - 1, targetType, replaceType, UP);
            floodFill(x - 1, y, targetType, replaceType, LEFT);
            floodFill(x + 1, y, targetType, replaceType, RIGHT);
        }
        return;
    case LEFT:
        if(x-1 >= 0 && y-1 >= 0 && y+1 < HEIGHT - 1 && 
           map->grid[x][y-1]->type == EMPTY && map->grid[x][y+1]->type == EMPTY && map->grid[x-1][y]->type == EMPTY) {
            map->grid[x][y] = mkFloor(x, y);
            floodFill(x - 1, y, targetType, replaceType, LEFT);
            floodFill(x, y - 1, targetType, replaceType, UP);
            floodFill(x, y + 1, targetType, replaceType, DOWN);
        }
        return;
    case RIGHT:
        if(x+1 < WIDTH - 1 && y-1 >= 0 && y+1 < HEIGHT - 1 && 
           map->grid[x][y-1]->type == EMPTY && map->grid[x][y+1]->type == EMPTY && map->grid[x+1][y]->type == EMPTY) {
            map->grid[x][y] = mkFloor(x, y);
            floodFill(x + 1, y, targetType, replaceType, RIGHT);
            floodFill(x, y - 1, targetType, replaceType, UP);
            floodFill(x, y + 1, targetType, replaceType, DOWN);
        }
        return;

    default:
        break;
    }

    // switch (direction)
    // {
    // case DOWN:
    //     if(y+2 > HEIGHT - 1 || map->grid[x][y+2]->type != EMPTY) {
    //         floodFill(x - 1, y, targetType, replaceType, LEFT);
    //         floodFill(x + 1, y, targetType, replaceType, RIGHT);
    //         break;
    //     }
    //     floodFill(x, y + 1, targetType, replaceType, DOWN);
    //     break;
    // case UP:
    //     if(y-2 < 0 || map->grid[x][y-2]->type != EMPTY) {
    //         floodFill(x - 1, y, targetType, replaceType, LEFT);
    //         floodFill(x + 1, y, targetType, replaceType, RIGHT);
    //         break;
    //     }
    //     floodFill(x, y - 1, targetType, replaceType, UP);
    //     break;
    // case LEFT:
    //     if(x-2 < 0 || map->grid[x-2][y]->type != EMPTY) {
    //         floodFill(x, y - 1, targetType, replaceType, UP);
    //         floodFill(x, y + 1, targetType, replaceType, DOWN);
    //         break;
    //     }
    //     floodFill(x - 1, y, targetType, replaceType, LEFT);
    //     break;
    // case RIGHT:
    //     if(x+2 > WIDTH - 1 || map->grid[x+2][y]->type != EMPTY) {
    //         floodFill(x, y + 1, targetType, replaceType, DOWN);
    //         floodFill(x, y - 1, targetType, replaceType, UP);
    //         break;
    //     }
    //     floodFill(x + 1, y, targetType, replaceType, RIGHT);
    //     break;

    // default:
    //     break;
    // }

    //OLD OLD
    // floodFill(x, y + 1, targetType, replaceType, UP);
    // floodFill(x, y - 1, targetType, replaceType, DOWN);
    // floodFill(x - 1, y, targetType, replaceType, LEFT);
    // floodFill(x + 1, y, targetType, replaceType, RIGHT);

    return;
}

/*
 * clears the screen then prints the map onto the standard window
 */
void printMapGrid(MapGrid *map)
{
    for (int y = 0; y < map->height; y++)
    {
        move(y, 0);
        for (int x = 0; x < map->width; x++)
        {
            delch();
            if (map->grid[x][y]->seen)
            {
                if (map->grid[x][y]->creature != NULL && map->grid[x][y]->visible)
                {
                    addch(map->grid[x][y]->creature->type);
                }
                else
                {
                    addch(map->grid[x][y]->type);
                }
            }
            else
            {
                addch(EMPTY);
            }
        }
    }
}
