#include "global.h"

/*
 * Creates a MapGrid pointer from a level text file
 */
MapGrid *mkMapGrid()
{
    MapGrid *map = (MapGrid *)malloc(sizeof(MapGrid));

    map->height = HEIGHT;
    map->width = WIDTH;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            map->grid[x][y] = mkCell(x, y);
        }
    }

    srand(time(NULL));
    map->num_rooms = 0;

    for (int i = 0; i < MAX_ROOMS; i++)
    {
        int w = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;
        int h = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;

        int x = rand() % (WIDTH - w - 1);
        int y = rand() % (HEIGHT - h - 1);

        Room *new_room = mkRoom(x, y, h, w);

        int intersects = 0;
        for (int j = 0; j < map->num_rooms; j++)
        {
            if (intersect(new_room, map->rooms[j]))
            {
                intersects = 1;
            }
        }

        if (intersects == 0)
        {
            map->rooms[map->num_rooms++] = new_room;
            addRoom(new_room, map);
        }
    }

    for (int i = 1; i < map->num_rooms; i++)
    {
        int VorH = rand() % 1;

        int x1 = map->rooms[i - 1]->center.x;
        int y1 = map->rooms[i - 1]->center.y;
        int x2 = map->rooms[i]->center.x;
        int y2 = map->rooms[i]->center.y;

        if (VorH)
        {
            addTunnelH(map, x1, x2, y1);
            addTunnelV(map, y1, y2, x2);
        }
        else
        {
            addTunnelV(map, y1, y2, x1);
            addTunnelH(map, x1, x2, y2);
        }
    }

    map->grid[map->rooms[1]->center.x][map->rooms[1]->center.y]->creature = mkCreature('T', map->rooms[1]->center.x, map->rooms[1]->center.y);
    map->player = mkCreature('@', map->rooms[0]->center.x, map->rooms[0]->center.y);

    return map;
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
            map->grid[x][y]->visible = 0;
        }
    }

    for (int i = 0; i < map->num_rooms; i++)
    {
        if (inRoom(map->rooms[i], map->player->pos.x, map->player->pos.y))
        {
            for (int x = map->rooms[i]->pos1.x; x <= map->rooms[i]->pos2.x; x++)
            {
                for (int y = map->rooms[i]->pos1.y; y <= map->rooms[i]->pos2.y; y++)
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

/*
 * clears the screen then prints the map onto the standard window
 */
void printMapGrid(MapGrid *map)
{
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            mvdelch(y, x);
            if (map->grid[x][y]->seen)
            {
                if (map->grid[x][y]->creature != NULL && map->grid[x][y]->visible)
                {
                    mvaddch(y, x, map->grid[x][y]->creature->type);
                }
                else
                {
                    mvaddch(y, x, map->grid[x][y]->tile->type);
                }
            }
            else
            {
                mvaddch(y, x, ' ');
            }
        }
    }
}
