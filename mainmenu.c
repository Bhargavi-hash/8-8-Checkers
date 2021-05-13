#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "Undo_Review.h"
#include "future_moves.h"

int main(void)
{
    GameState G = initEmptyBoard();
    setBoard(G);
    displayBoardClear(G);
    struct Node *head = GetNewNode(*G);

    int x = 0, y = 0, tX = 0, tY = 0;
    //need to include a provision to restrict moves if a capture is available
    while (1)
    {
        char str[10];
        if(!winLose(G)){
            displayBoardClear(G);
            if(G->currPlayer == BLACK)
                printf("Black ");
            else
                printf("Red ");
            printf("lost the game!\n");
            
            printf("Enter \"newgame\" or \"n\" to start a new game.\n");
            scanf("%s",str);

            if(!strcmp(str, "continue") || !strcmp(str, "c")){
                G = initEmptyBoard();
                setBoard(G);
                continue;
            }
            else
                break;
        }

        // displayBoardClear(G);
        printf("Enter a command\n");
        scanf("%s", str);

        if(!strcmp(str, "h") || !strcmp(str, "help") || !strcmp(str, "HELP") || !strcmp(str, "Help")){
            system("clear");
            printf("move / m\t--moves a piece\n");
            printf("undo / u\t--undo's a move\n");
            printf("review / r\t--reviews the game from the beginning\n");
            printf("reset / R / ff\t--resets the game\n");
            printf("future / f\t--prints every possible board state 'k' moves in the future\n");
            printf("exit / x\t--exits the program\n\n");
            
            printf("Enter a character to resume playing\n");
            char buffer,q;
            if(scanf("%c%c",&buffer,&q)){
                displayBoardClear(G);
                continue;
            }
        }
        //need to undo for X moves
        else if(!strcmp(str, "undo") || !strcmp(str, "u")){
            int k;
            displayBoardClear(G);
            printf("How many moves should be undone?\n");
            if(scanf("%d",&k)){
                G = Undo(head, k);
                displayBoardClear(G);
            }
            continue;
        }
        else if(!strcmp(str, "review") || !strcmp(str, "r")){
            system("clear");
            Review(head);

            printf("Enter a character to resume playing\n");
            char buffer,q;
            if(scanf("%c%c",&buffer,&q)){
                displayBoardClear(G);
                continue;
            }
            continue;
        }
        else if(!strcmp(str, "future") || !strcmp(str, "f")){
            int k;
            printf("How many moves into the future? (More than 3 moves isnt recommended for dense boards)\n");
            scanf("%d",&k);

            system("clear");
            FTree F = createFTree(k, G);
            displayFTree(k, F);
            freeFTree(F);
            
            printf("Enter a character to resume playing\n");
            char buffer,q;
            if(scanf("%c%c",&buffer,&q)){
                displayBoardClear(G);
                continue;
            }

            continue;
        }
        else if(!strcmp(str, "reset") || !strcmp(str, "R") || !strcmp(str, "ff")){
            char k,buffer,d;
            printf("Are you sure? (Y,N) \n");
            scanf("%c%c%c",&d,&k,&buffer);

            if(k == 'Y' || k == 'y'){
                G = initEmptyBoard();
                setBoard(G);
                displayBoardClear(G);
                
                struct Node* temp = head;
                while(temp != NULL){
                    struct Node* tt = temp;
                    temp = temp->next;
                    free(tt);
                }
                head = GetNewNode(*G);

                continue;
            }
            else{
                continue;
            }
        }
        else if (!strcmp(str, "exit") || !strcmp(str, "x")){
            break;
        }
        else if(!strcmp(str, "move") || !strcmp(str, "m")){
            displayBoardClear(G);
            printf("Enter x and y coordinates of the piece you want to move and the target square\n");
        
            if (!scanf(" %d %d %d %d", &x, &y, &tX, &tY)){
                displayBoardClear(G);
                printf("Invalid entries, enter \"HELP\" for the list of accepted commands");
                continue;
            }

            x--; y--;tX--; tY--;

            if (x == -1 && y == -1 && tX == -1 && tY == -1){
                struct Node* temp = head;
                while(temp != NULL){
                    struct Node* tt = temp;
                    temp = temp->next;
                    free(tt);
                }
                break;
            }

            int status = movePiece(G, x, y, tX, tY);
            if(status == 1 || status == 2 || status == 3) 
                insert(G, head);
            displayBoardClear(G);

            switch (status){
            default:
            case 0:
                printf("Invalid move.\n");
                break;
            case -1:
                printf("You must make a capture.\n");
                break;
            case 1:
                printf("You made a regular move.\n");
                break;
            case 2:
                printf("You captured a piece, you must make another capture if possible.\n");
                break;
            case 3:
                printf("You promoted a pawn.\n");
                break;
            }
        }
        //default
        else{
            displayBoardClear(G);
            printf("Invalid command, enter \"HELP\" for the list of accepted commands\n");
            continue;   
        }
    }

    if(G != NULL)
        free(G);
    return 0;
}
