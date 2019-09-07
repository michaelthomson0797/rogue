#include "global.h"

RoomNode *mkRoomNode(Room *room)
{
  RoomNode *roomNode = malloc(sizeof(RoomNode));
  roomNode->room = room;
  roomNode->next = NULL;
  return roomNode;
}

void appendRoom(Room *room, RoomNode* roomHead)
{
  RoomNode *currRoomNode;
  for(currRoomNode = roomHead; currRoomNode->next != NULL; currRoomNode = currRoomNode->next){}
  currRoomNode->next = mkRoomNode(room);
}
