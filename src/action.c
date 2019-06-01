#include "global.h"

Action *mkAction(int type, Actor *actor, int x, int y) {
  Action *action = malloc(sizeof(Action));

  action->type = type;
  action->actor = actor;
  action->x = x;
  action->y = y;

  return action;
}

void attack(Actor *attacker, Actor *defender) {
  attacker->energy = attacker->energy-20;

  defender->health = defender->health - attacker->damage;
}

void walk(Actor *actor, int x, int y) {

  actor->energy = actor->energy-20;
  
  // check if out of bounds
  if(x >= map->width || x < 0 || y >= map->height || y < 0) {
    return;
  }

  // check if an actor exists there
  if(map->grid[y][x]->actor != NULL) {
    attack(actor, map->grid[y][x]->actor);
    return;
  }

  // check if we can walk there
  if(map->grid[y][x]->passable == 0) {
    return;
  }
  
  // move actor
  map->grid[actor->y][actor->x]->actor = NULL;

  actor->x = x;
  actor->y = y;
  map->grid[y][x]->actor = actor;
}

void kill(Actor *actor) {
  map->grid[actor->y][actor->x]->appearance = 'X';
  map->grid[actor->y][actor->x]->actor = NULL;
}

void performAction(Action *action) {
  switch (action->type)
  {
  case WALK:
    walk(action->actor, action->x, action->y);
    break;
  
  case WAIT:
    break;

  case DIE:
    kill(action->actor);
    break;

  default:
    break;
  }
}