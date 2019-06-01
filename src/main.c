#include "global.h"

int main() 
{
  game = malloc(sizeof(Game));

  game->actorHead = NULL;
  game->currentActorNode = NULL;

  run(game);

  return 0;
}