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

void removeActor(Game *game, ActorNode *actorNode) {
  ActorNode *n = game->actorHead;
  while(n->next != actorNode) {
    n = n->next;
  }
  n->next = n->next->next;
  actorNode->next = NULL;
}