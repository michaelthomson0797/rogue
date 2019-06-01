#include "global.h"

void run()
{
  srand(time(NULL));

  // Generate the map
  map = mkMap();

  // initialize astar
  nodeSource = malloc(sizeof(ASPathNodeSource));
  nodeSource->nodeSize = sizeof(Tile);
  nodeSource->nodeNeighbors = &nodeNeighbors;
  nodeSource->pathCostHeuristic = &pathCostHeuristic;

  // create the hero
  addActor(PLAYER, 20, 5);

  // create some monsters
  addActor(GOBLIN, 28, 7);

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

void process()
{
  Action *action = getAction(game->currentActorNode->actor);
  performAction(action);
  nextActor(game);
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