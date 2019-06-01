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
    return mkGenericActor(PLAYER, '@', 10, 5, x, y);
  
  case MONSTER:
    return mkGenericActor(MONSTER, 'T', 10, 10, x, y);
  
  default:
    break;
  }

  return NULL;
}

Action *getAction(Actor *actor) {

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
    }
  }

  if(actor->type == MONSTER) {
    srand(time(NULL));
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