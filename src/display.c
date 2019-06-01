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
void render(Map *map, Game *game) {

  // prints the map
  for(int y = 0; y < map->height; y++) {
    move(y,0);
    for(int x = 0; x < map->width; x++) {
      delch();
      addch(getAppearance(map->grid[y][x]));
    }
  }

  // prints the player information
  move(0,map->width);
  printw(" Player:");
  move(1,map->width);
  printw(" %c [", game->actorHead->actor->appearance);

  int l = game->actorHead->actor->health / 5;

  for(int i = 0; i < 20; i++) {
    i < l ? addch('=') : addch(' ');
  }

  addch(']');


  refresh();
}