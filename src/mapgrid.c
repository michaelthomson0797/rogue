#include "global.h"

/*
 * Creates a MapGrid pointer from a level text file
 */
MapGrid* mkMapGrid(char filename[]) {
    MapGrid* map = (MapGrid*) malloc(sizeof(MapGrid));

    map->height = HEIGHT;
    map->width = WIDTH;
    map->rooms = (Room**) malloc(MAX_ROOMS * sizeof(Room*));
    map->grid = (Tile***) malloc(map->width * sizeof(Tile**));

    for(int i = 0; i < map->width; i++) {
        map->grid[i] = (Tile**) malloc(map->height * sizeof(Tile*));
    }

   for(int y = 0; y < map->height; y++) {
       for(int x = 0; x < map->width; x++) {
           map->grid[x][y] = mkEmpty(x, y);
       }
   }

   srand(time(NULL));
    int num_rooms = 0;

    for(int i = 0; i < MAX_ROOMS; i++) {
        int w = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;
        int h = rand() % MAX_ROOM_SIZE + MIN_ROOM_SIZE;

        int x = rand() % (WIDTH - w - 1);
        int y = rand() % (HEIGHT - h - 1);

        Room* new_room = mkRoom(x, y, h, w);

        int intersects = 0;
        for(int j = 0; j < num_rooms; j++) {
            if(intersect(new_room, map->rooms[j])) {
                intersects = 1;
            }
        }
        
        printf("%d", num_rooms);
        
        if(intersects == 0) {
            map->rooms[num_rooms++] = new_room;
            addRoom(new_room, map);
        }
    }

    for(int i = 1; i < num_rooms; i++) {
        int VorH = rand() % 1;

        int x1 = map->rooms[i-1]->center.x;
        int y1 = map->rooms[i-1]->center.y;
        int x2 = map->rooms[i]->center.x;
        int y2 = map->rooms[i]->center.y;

        if(VorH) {
            addTunnelH(map, x1, x2, y1);
            addTunnelV(map, y1, y2, x2);
        } else {
            addTunnelV(map, y1, y2, x1);
            addTunnelH(map, x1, x2, y2);
        }
    }


    map->player = mkCreature('@', map->rooms[0]->center.x, map->rooms[0]->center.y);

    return map;

}

/*
 * clears the screen then prints the map onto the standard window
 */
void printMapGrid(MapGrid* map) {
   for(int y = 0; y < map->height; y++) {
       for(int x = 0; x < map->width; x++) {
           mvdelch(y, x);
           if(map->grid[x][y]->playerPresent) {
                mvaddch(y, x, '@');
           } else {
                mvaddch(y, x, map->grid[x][y]->type);
           }
       }
   }
}

