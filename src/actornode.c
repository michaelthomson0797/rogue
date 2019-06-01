#include "global.h"

ActorNode *mkActorNode(Actor *actor) {
  ActorNode *actorNode = malloc(sizeof(ActorNode));
  actorNode->actor = actor;
  actorNode->next = NULL;
  return actorNode;
}

void appendActor(Game *game, Actor *actor) {
  if(game->actorHead == NULL) {
    game->actorHead = mkActorNode(actor);
    return;
  }
  
  ActorNode *n = game->actorHead;

  while(n->next != NULL) {
    n = n->next;
  }
  n->next = mkActorNode(actor);
}

void removeActor(Game *game, Actor *actor) {
  ActorNode *n = game->actorHead;
  while(n->next->actor != actor) {
    n = n->next;
  }
  ActorNode *temp = n->next;
  n->next = n->next->next;
  temp->next = NULL;
}