#include "global.h"

Creature* creatureFind(Creature** head, Creature* currentCreature) {
    Creature* x = (*head);

    while(x != currentCreature && x != NULL) {
        x = x->next;
    }

    return x;
}

int creatureInsert(Creature** head, Creature* currentCreature)
{
    currentCreature->next = (*head);
    currentCreature->prev = NULL;

    if((*head) != NULL) {
        (*head)->prev = currentCreature;
    }

    (*head) = currentCreature;
}

void creatureDelete(Creature** head, Creature* currentCreature)
{
    Creature* x = creatureFind(head, currentCreature);
    if(x == NULL) {
        return;
    }
    if(x->prev != NULL) {
        x->prev->next = x->next;
    } else {
        *head = x->next;
    }
    if(x->next != NULL) {
       x->next->prev = x->prev;
    }
    return;
}

void printLinkedList(Creature* head) 
{
    for(Creature* x = head; x != NULL; x = x->next) {
        printf("%d ", x->type);
    }
    printf("\n");
}
