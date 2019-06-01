#include "global.h"

void run(Game *game)
{
  // Generate the map
  map = mkMap();

  // create the hero
  addActor(game, PLAYER, 20, 5);
  addActor(game, MONSTER, 30, 7);

  // set current actor
  game->currentActorNode = game->actorHead;

  initDisplay();

  render(map);

  int playing = 1;

  while(playing) {
    process(game);
    render(map);
  }

  endwin();
}

void process(Game *game)
{
  Action *action = getAction(game->currentActorNode->actor);
  performAction(action);
  nextActor(game);
}

// adds an actor to the map and the actor linked list
void addActor(Game *game, int type, int x, int y) {
  Actor *actor = map->grid[y][x]->actor = mkActor(type, x, y);
  appendActor(game, actor);
}

// sets the next actor in the linked list as the current
void nextActor(Game *game) {
  if(game->currentActorNode->next == NULL) {
    game->currentActorNode = game->actorHead;
    return;
  }

  game->currentActorNode = game->currentActorNode->next;
}