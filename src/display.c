#include "global.h"

// Initializes and opens the screen
void initDisplay() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
}

// renders a given map to the screen
void render(Map *map) {

  for(int y = 0; y < map->height; y++) {
    move(y,0);
    for(int x = 0; x < map->width; x++) {
      delch();
      addch(getAppearance(map->grid[y][x]));
    }
  }

  refresh();
}