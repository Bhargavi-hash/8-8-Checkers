#ifndef __BASE_GAME_H
#define __BASE_GAME_H

//leaving this in to allow for differently sized boards
#define SIZE 8


//allows for convenient conditionals
//eg. !RED => BLACK, and the same goes for pawns and kings
#define RED 1
#define BLACK 0
#define PAWN 0
#define KING 1

// 100: empty square
// 000: black pawn
// 001: black king
// 010: red pawn
// 011: red king

#define EMPTY 0b100
#define BLACK_PAWN 0b000
#define BLACK_KING 0b001
#define RED_PAWN 0b010
#define RED_KING 0b011

//Turn stores the current turn, curr_player stores whose move it is 
struct GameStateS{
    int turn;
    int currPlayer;
    short int board[8][8];
};
typedef struct GameStateS* GameState;

//REMEMBER TO FREE DECLARED GAME STATES
GameState initEmptyBoard();
void setBoard(GameState G);
void copyBoard(GameState src, GameState dest);
void freeBoard(GameState G);

//doesnt overwrite pieces, returns if non empty piece
void addPiece(GameState G, int x, int y, int colour, int type);
void removePiece(GameState G, int x, int y);

//moves a piece from (x,y) to the target location if possible
int movePiece(GameState G, int x, int y, int targetX, int targetY);
void updateBoard(GameState G);
int winLose(GameState G);

//prints a gamestate w/out and after clearing the terminal respectively
void displayBoard(GameState G);
void displayBoardClear(GameState G);

int isEmpty(GameState G, int x, int y);
int validMove(GameState G, int x, int y);
int captureAvailable(GameState G, int x, int y);

#endif
