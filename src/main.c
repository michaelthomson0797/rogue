#include "global.h"

int main() 
{
  // seed random number
  srand(time(NULL));
  
  game = malloc(sizeof(Game));

  game->actorHead = NULL;
  game->currentActorNode = NULL;

  run(game);

  return 0;
}
