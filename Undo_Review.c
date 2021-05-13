#include <stdio.h>
#include <stdlib.h>
#include "Undo_Review.h"
#include "game.h"


// To create a new node with its content as GameStateS G and next and prev NULL and returns pointer to it. 
struct Node *GetNewNode(struct GameStateS G)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    copyBoard(&G, &(newNode->G1));
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//Insert the GameStateS G at the tail of the linked list
void insert(GameState G, struct Node *head)
{
    struct Node *temp = head;
    struct Node *newNode = GetNewNode(*G);
    if (head == NULL)
    {
        GameState tt = initEmptyBoard();
        setBoard(tt);
        head = GetNewNode(*tt);
        return;
    }
   
    while (temp->next != NULL)
    {
        temp = temp->next; // Go To last Node
    }
    temp->next = newNode;
    newNode->prev = temp;
}

//Undoing the latest move by deleting the last node and returning the node previous to the it
GameState Undo(struct Node *head, int k)
{
    if (head->next == NULL)
    {
        GameState F = initEmptyBoard();
        setBoard(F);// Go to initial state of the board
        return F;
    }

    GameState H;

    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;// Go To last Node

    for(int i = 0; i < k; i++){
        if(temp->prev != NULL){
            temp = temp->prev;
            free(temp->next);
            temp->next = NULL;
        }
        else break;
    }
    
    // H = &temp->prev->G1;//return the node previous to last one
    // temp->prev->next = NULL;
    // free(temp);//Delete the last node

    // return H;

    return &(temp->G1);
}

// Print all the moves played by the players from start
void Review(struct Node *head)
{
    struct Node *temp = head;
    // if (head->next== NULL)
    // {
    //     printf("There have been no moves lol\n");
    //     return;
    // }
    while (temp != NULL)
    {
        displayBoard(&temp->G1);
        temp = temp->next;
    }
}
