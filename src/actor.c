#include "global.h"

// generic constructor for new actor
Actor *mkGenericActor(int type, char appearance, int energy, int speed, int x, int y)
{
  Actor *actor = malloc(sizeof(Actor));

  actor->type = type;
  actor->appearance = appearance;
  actor->energy = energy;
  actor->speed = speed;
  actor->x = x;
  actor->y = y;

  return actor;
}

// abstracted actor creation
Actor *mkActor(int type, int x, int y)
{
  switch (type)
  {
  case PLAYER:
    return mkGenericActor(PLAYER, '@', 12, 6, x, y);
  
  case GOBLIN:
    return mkGenericActor(GOBLIN, 'G', 12, 3, x, y);

  case SLUG:
    return mkGenericActor(SLUG, 'S', 12, 2, x, y);

  case CHEETAH:
    return mkGenericActor(CHEETAH, 'C', 12, 12, x, y);
  
  default:
    break;
  }

  return NULL;
}

// given an actor, this will return an action that the actor
// would like to perform
Action *getAction(Actor *actor) {

  // if there is not enough energy, the creature waits
  if(actor->energy < ENERGYCOST) {
      actor->energy += actor->speed;
      return mkAction(WAIT, actor, actor->x, actor->y);
  }

  if(actor->type == PLAYER) {
    int ch = getch();
    switch (ch)
    {
      case KEY_LEFT:
        return mkAction(WALK, actor, actor->x-1, actor->y);
      
      case KEY_RIGHT:
        return mkAction(WALK, actor, actor->x+1, actor->y);

      case KEY_UP:
        return mkAction(WALK, actor, actor->x, actor->y-1);

      case KEY_DOWN:
        return mkAction(WALK, actor, actor->x, actor->y+1);

      case 'c':
        return mkAction(WAIT, actor, actor->x, actor->y);
    }
  }

  if(actor->type != PLAYER) {
    
    int r = rand() % 4;
    switch (r)
    {
      case 0:
        return mkAction(WALK, actor, actor->x-1, actor->y);
      
      case 1:
        return mkAction(WALK, actor, actor->x+1, actor->y);

      case 2:
        return mkAction(WALK, actor, actor->x, actor->y-1);

      case 3:
        return mkAction(WALK, actor, actor->x, actor->y+1);
    }
  }

  return NULL;
}