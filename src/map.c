#include "global.h"

Map *mkMap() {

  Map *map = malloc(sizeof(Map));

  map->height = HEIGHT;
  map->width = WIDTH;

  FILE *file = fopen("testmap.txt", "r");
  char c;

  if(file == NULL)
    return NULL;

  for(int i = 0; i < HEIGHT; i++) {
    for(int j = 0; j < WIDTH; j++) {
      c = (char) fgetc(file);
      
      switch (c)
      {
      case '#':
        map->grid[i][j] = mkTile(WALL, j, i);
        break;
      
      case '.':
        map->grid[i][j] = mkTile(FLOOR, j, i);
        break;
      
      default:
        break;
      }

    }
    c = (char) fgetc(file);
  }
  return map;
}