#include "future_moves.h"

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//      the data structure used for this feature involves a tree of linked lists (arbitrary number of children per node)
//      each node stores a GameState, and each of its children store GameStates that can be achieved in one move
//      the children of a node are stored in a linked list
//      each node stores a pointer to the head of the linked list of its children, and a 
//      pointer to the next node in its own linked list (its sibling)
//      nodes also store a 'depth' variable for easier printing
//      this data structure is referred to as an FTree in this project

//hidden fn that mallocs and initialises a node in the 'future moves' tree
FNode _initFNode(int depth, GameState G){
    FNode node = (FNode) malloc(sizeof(struct FutureTreeNode));
    node->child = NULL;
    node->next = NULL;
    node->G = initEmptyBoard();
    copyBoard(G, node->G);
    node->depth = depth;
    return node;
}

FNode _addChild(FNode parent, GameState G){
    parent->child = _initFNode(parent->depth + 1, G);
    return  parent->child;
}

FNode _addSibling(FNode elder, GameState G){
    FNode temp = elder;
    while(temp->next != NULL)
        temp = temp->next;
    
    temp->next = _initFNode(elder->depth, G);

    return temp->next;
}

//displays each possible gamestate after 'depth' moves
//this function recursively prints every node at depth 'k' of the tree
void displayFTree(int depth, FTree F){
    
    if(F == NULL || F->depth > depth){
        return;
    }
    
    FTree temp = F;
    if(temp->depth == depth){
        while(temp != NULL){
            printf("Depth: %d\n", temp->depth);
            displayBoard(temp->G);
            printf("\n");
            temp = temp->next;
        }
        // printf("--------------------\n");
        return;
    }

    while(temp != NULL){
        displayFTree(depth, temp->child);
        temp = temp->next;
    }
}

//recursively frees an FTree in a sort of post-order traversal
void freeFTree(FTree F){
    if(F == NULL)
        return;

    FNode temp = F;

    while(temp != NULL){
        FNode nexttemp = temp->next;
        
        freeFTree(temp->child);
        free(temp->G);
        free(temp);

        temp = nexttemp;
    }
}

//adds the next layer of moves to an FNode
//the board is scanned and an new FNode is made for each legal move possible from the GameState in F
//checks are included to force captures if possible, decide between captures if more than one is possible
//accounts for king moves, promotions and multi-jumps
//since the number of moves increase very rapidly, it takes a significant amount of time to display every possible move for
//more than three moves for boards early on in matches
//for sparser, lategame boards, ~8 moves can be calculated within a feasible amount of time
//white squares arent searched as an optimisation
FTree _nextChildren(FNode F){
    GameState G = F->G;

    int canCapture = 0;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            if((i+j)%2 == 1 && (G->board[i][j] >> 1) == G->currPlayer && captureAvailable(G,i,j))
                canCapture = 1;
        }

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            if((i+j)%2 == 1){
                if((G->board[i][j] >> 1) == G->currPlayer && !isEmpty(G, i, j) && validMove(G, i, j)){
                    short int tempPiece = G->board[i][j];
                    if(tempPiece == BLACK_KING || tempPiece == RED_KING){
                        
                        if(captureAvailable(G,i,j)){
                            for(int k = -1; k < 2; k +=2)
                                for(int l = -1; l < 2; l +=2)
                                    if(validMove(G, i + k*2, j + l*2) && isEmpty(G, i + k*2, j + l*2)){
                                        GameState tempBoard = initEmptyBoard();
                                        copyBoard(G, tempBoard);

                                        movePiece(tempBoard, i, j, i + k*2, j + l*2);
                                        //assuming F has a child
                                        if(F->child == NULL)
                                            _addChild(F, tempBoard);
                                        else
                                            _addSibling(F->child, tempBoard);
                                        
                                        free(tempBoard);
                                    }
                        }
                        
                        else if(canCapture == 0){
                            for(int k = -1; k < 2; k +=2)
                                for(int l = -1; l < 2; l +=2)
                                    if(validMove(G, i + k, j + l) && isEmpty(G, i + k, j + l)){
                                        GameState tempBoard = initEmptyBoard();
                                        copyBoard(G, tempBoard);

                                        movePiece(tempBoard, i, j, i + k, j + l);
                                        //assuming F has a child
                                        if(F->child == NULL)
                                            _addChild(F, tempBoard);
                                        else
                                            _addSibling(F->child, tempBoard);
                                        
                                        free(tempBoard);
                                    }
                        }
                    }
                    else{
                        short int tempPieceColour = tempPiece >> 1;
                        int direction = ((tempPieceColour == RED) ? -1 : 1);

                        if(captureAvailable(G, i, j)){
                            for(int k = -1; k < 2; k +=2)
                                if(validMove(G, i + 2*k, j + 2*direction) && isEmpty(G, i + 2*k, j + 2*direction)){
                                    GameState tempBoard = initEmptyBoard();
                                    copyBoard(G, tempBoard);
                                    int status = movePiece(tempBoard, i, j, i + 2*k, j + 2*direction);
                                    //assuming F has a child
                                    if(F->child == NULL)
                                        _addChild(F, tempBoard);
                                    else
                                        _addSibling(F->child, tempBoard);
                                    
                                    free(tempBoard);        
                                }
                        }
                        else if(canCapture == 0){
                            for(int k = -1; k < 2; k +=2)
                                if(validMove(G, i + k, j + direction) && isEmpty(G, i + k, j + direction)){
                                    GameState tempBoard = initEmptyBoard();
                                    copyBoard(G, tempBoard);
                                    int status = movePiece(tempBoard, i, j, i + k, j + direction);
                                    //assuming F has a child
                                    if(F->child == NULL)
                                        _addChild(F, tempBoard);
                                    else
                                        _addSibling(F->child, tempBoard);
                                    
                                    free(tempBoard);        
                                }
                        }
                    }
                }
            }
        }

    return F->child;
}

//part of a recursive function that runs _nextChildren() once for every node in an FTree until the depth of the FTree reaches 'k'
//
void _createFTreeStep(int k, FNode F){
    
    if(F == NULL || F->depth == k)
        return;
        
    FNode temp = _nextChildren(F); //child of F
    while(temp != NULL){
        _createFTreeStep(k, temp);

        temp = temp->next;
    }    
}

//wrapper function that declares and inits an FTree
//this tree needs to be freed by the user
FTree createFTree(int k, GameState G){
    FTree tree = _initFNode(0, G);
    _createFTreeStep(k, tree);
    return tree;
}

//this feature could be improved by possibly including a data structure in 'GameState' like a vector that kept track of the location and
//type of each piece on both sides, like a vector with elements that are 5 bits each, that store the position and type of each piece
//while not an improvement to the complexity, the constant factor would be greatly reduced for lategame and endgame boards
//
//another possible improvement would be to try and maintain a running FTree that updates with every move
//once a move is made, that moves child node is made the root, and each of its siblings and their subtrees are discarded
//the depth to which the tree is made is set to the maximum depth called by the user so far
//if the future moves function is called repeatedly, this saves time that would be used in creating a new tree from scratch