#include "global.h"

void run()
{
  // Generate the map
  map = mkMap();

  // initialize astar
  nodeSource = malloc(sizeof(ASPathNodeSource));
  nodeSource->nodeSize = sizeof(Tile);
  nodeSource->nodeNeighbors = &nodeNeighbors;
  nodeSource->pathCostHeuristic = &pathCostHeuristic;

  // create the hero
  addActor(PLAYER, map->roomHead->room->lx+1, map->roomHead->room->ly+1);

  // create some monsters
  addActor(GOBLIN, map->roomHead->next->room->lx+1, map->roomHead->next->room->ly+1);

  // set current actor
  game->currentActorNode = game->actorHead;

  initDisplay();
  updateVisibility();
  render(map);

  int playing = 1;

  while(playing) {
    process(game);
    render(map);
  }

  endwin();
}

void process()
{
  Action *action = getAction(game->currentActorNode->actor);
  performAction(action);
  updateVisibility();
  nextActor();
}

// adds an actor to the map and the actor linked list
void addActor(int type, int x, int y) {
  Actor *actor = map->grid[y][x]->actor = mkActor(type, x, y);
  appendActor(actor);
}

// sets the next actor in the linked list as the current
void nextActor() {
  if(game->currentActorNode->next == NULL) {
    game->currentActorNode = game->actorHead;
    return;
  }

  game->currentActorNode = game->currentActorNode->next;
}
