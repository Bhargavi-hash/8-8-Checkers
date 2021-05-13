#ifndef __DOUBLYLL_H
#define __DOUBLYLL_H
#include "game.h"

struct Node
{
    struct GameStateS G1;
    struct Node *next; // Pointer to next node in DLL
    struct Node *prev; // Pointer to previous node in DLL
};

struct Node* GetNewNode(struct GameStateS G);
void insert(GameState G, struct Node *head);
GameState Undo(struct Node *head, int k);
void Review(struct Node *head);

#endif
