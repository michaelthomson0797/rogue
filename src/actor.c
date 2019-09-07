#include "global.h"

// generic constructor for new actor
Actor *mkGenericActor(int type, char appearance, int energy, int speed, int health, int damage, int x, int y)
{
  Actor *actor = malloc(sizeof(Actor));

  actor->type = type;
  actor->appearance = appearance;
  actor->energy = energy;
  actor->speed = speed;
  actor->health = health;
  actor->damage = damage;
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
    return mkGenericActor(PLAYER, '@', 12, 6, 100, 20, x, y);
  
  case GOBLIN:
    return mkGenericActor(GOBLIN, 'G', 12, 4, 10, 10, x, y);

  case SLUG:
    return mkGenericActor(SLUG, 'S', 12, 2, 50, 10, x, y);

  case CHEETAH:
    return mkGenericActor(CHEETAH, 'C', 12, 12, 20, 80, x, y);
  
  default:
    break;
  }

  return NULL;
}

// given an actor, this will return an action that the actor
// would like to perform
Action *getAction(Actor *actor) {

  // check if the creature is dead
  if(actor->health <= 0) {
    return mkAction(DIE, actor, actor->x, actor->y);
  }

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

      case KEY_HOME:
        return mkAction(WALK, actor, actor->x-1, actor->y-1);

      case KEY_PPAGE:
        return mkAction(WALK, actor, actor->x+1, actor->y-1);

      case KEY_END:
        return mkAction(WALK, actor, actor->x-1, actor->y+1);

      case KEY_NPAGE:
        return mkAction(WALK, actor, actor->x+1, actor->y+1);

      default:
        return mkAction(WAIT, actor, actor->x, actor->y);
    }
  }

  if(actor->type != PLAYER) {
    int sx = actor->x;
    int sy = actor->y;
    int tx = game->actorHead->actor->x;
    int ty = game->actorHead->actor->y;
    Tile *source = map->grid[sy][sx];
    Tile *target = map->grid[ty][tx];


    ASPath path = ASPathCreate(nodeSource, NULL, source, target);

    Tile *step = (Tile *)ASPathGetNode(path, 1);

    if (step == NULL){
      return mkAction(WAIT, actor, actor->x, actor->y);
    }

    return mkAction(WALK, actor, step->x, step->y);
  }

  return NULL;
}
