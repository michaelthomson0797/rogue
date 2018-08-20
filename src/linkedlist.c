#include "global.h"

Creature* creatureFind(Creature** head, Creature* currentCreature) {
    Creature* x = (*head);

    while(x != currentCreature && x != NULL) {
        x = x->next;
    }

    return x;
}

void creatureInsert(Creature** head, Creature* currentCreature)
{
    Creature* x = (*head);

    if((*head) == currentCreature) {
        return;
    }

    while(x->next != NULL) {
        x = x->next;
    }

    x->next = currentCreature;
    x->next->next = NULL;
    x->next->prev = x; 
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
        printf("%c ", x->type);
    }
    printf("\n");
}
