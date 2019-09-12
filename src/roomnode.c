#include "global.h"

RoomNode *mkRoomNode(Room *room)
{
  RoomNode *roomNode = malloc(sizeof(RoomNode));
  roomNode->room = room;
  roomNode->next = NULL;
  return roomNode;
}

void appendRoom(Room *room)
{
  if (map->roomHead == NULL) {
    map->roomHead = mkRoomNode(room);
    return;
  }
  
  RoomNode *currRoomNode;

  for(currRoomNode = map->roomHead; currRoomNode->next != NULL; currRoomNode = currRoomNode->next){}
  currRoomNode->next = mkRoomNode(room);
}
