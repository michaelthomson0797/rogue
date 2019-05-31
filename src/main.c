#include "global.h"

int main() 
{
  Game *game = malloc(sizeof(Game));

  game->actorHead = NULL;
  game->currentActorNode = NULL;

  run(game);

  return 0;
}