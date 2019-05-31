#include "global.h"

Actor *hero;

void process(Game *game)
{
  Action *action = getAction(hero);
  performAction(action);
}

void run(Game *game)
{
  map = mkMap();

  hero = map->grid[5][20]->actor = mkActor(PLAYER, 20, 5);

  initDisplay();

  render(map);

  int playing = 1;

  while(playing) {
    process(game);
    render(map);
  }

  endwin();
}

