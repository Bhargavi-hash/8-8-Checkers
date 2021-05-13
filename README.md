# 8-8 Checkers
Checkers (also known as Draughts) is a popular group of board games. The most commonly played one is an 8x8 version of American Checkers (also known as English Draughts). Here, we will be developing a terminal version of this game.

# Features
1. A feature to UNDO as many moves as asked by the players (provided both players agree).
2. A feature to REVIEW the game from the start, so the players can see what led to the current game state if they wish to.
3. A feature to SHOW ALL POSSIBLE MOVES for the next k turns (if both players make a move each, that is counted as two turns), where k is a number that the player gives.

# Checker Board Numbering
![Untitled drawing (1)](https://user-images.githubusercontent.com/82858718/115566952-5c4b3380-a2d8-11eb-9fee-145db79de448.png)

# Checker-board RULES
1. Each player starts with 12 men on the dark squares of the 3 rows nearest to that players side.
2. Each player is assinged a different color.
3. The men of each player can move only in the dark squares and only diagnol moves are possible.
4. The row closest to each player is called the kings row or crownhead.
5. The player with the darker-coloured pieces moves first. Then plays the second player.
6. Once a piece is kinged, the player must wait until the next turn to jump out of the king row. This applies to multi-jumps as well.
7. You win the game when the opponent has no more pieces or can't move (even if he/she still has pieces). If neither player can move then it is a draw or a tie.

# Move Rules
There are two different ways to move in English draughts:

## Simple move:

A simple move consists of moving a piece one square diagonally to an adjacent unoccupied dark square. 
Uncrowned pieces can move diagonally forward only; kings can move in any diagonal direction.

## Jump:

A jump consists of moving a piece that is diagonally adjacent an opponent's piece, to an empty square immediately beyond it in the same direction (thus "jumping over" the opponent's piece front and back ). 
Men can jump diagonally forward only; kings can jump in any diagonal direction. A jumped piece is considered "captured" and removed from the game. Any piece, king or man, can jump a king. 

>> NOTE:
If a player has the option to jump, he must take it, even if doing so results in disadvantage for the jumping player.

## CaptureAvailable 
This function returns 1 if there is a capture available and 0 if there is no capture available. 
The arguments to this function are the pointer to the GameStateS I.e., GameState and two integer parameters that represent the coordinates of the piece on the checker board. 
Now we have two cases to deal with. One when our piece is a King, and another our piece is Pawn. 
>> Case 1: King 
A King can move in all four directions I.e., right and left to the front and right and left to the back. 
                          
We have used two “for” loops to encounter these 4 cases. These will run in constant time. 
Now we check whether a particular move is valid or not. If valid, then whether it can make a capture or not. 
If a successful capture can be made, then the function returns 1 and if a capture is not possible then it returns 0.  
                                   
>> Case 2: Pawn 
 A pawn can move only in one direction I.e., forward or backward. A red Pawn                 
 will  move downward on the board. Hence the Y coordinate is reduced by 1. And  
 a black  pawn will move towards the top on the board and hence the Y 
 coordinate is incremented by 1. 
                         
Now like the previous case it checks for a valid move and a valid capture if                                          
available, and returns 1 or 0 accordingly.  

## ValidMove
This is a simple function to check whether a given move is valid or not.
We pass the Gamestate pointer, and two integers representing the coordinates of the new position as parameters. 
Now if the coordinates entered exceeds the bounds then the function will return 0.
Now if the coordinates are within the bounds then if the coordinate lies at a white space then the function returns 0, otherwise it returns a 1.

## IsEmpty
This is a simple function to check whether a particular space on the checker board is Empty or not.
If it is Empty then the function returns 1, else it returns a 0.

## DisplayBoard
This function is implemented to print the Board on the Terminal.
Firstly it prints the current Turn number which is stored in the GameStateS struct. And then prints the player ( Red or Black ).
Two nested for loops are used to print the board. Each loop runs for a constant time. So the overall running time of both the loops together will be constant.

## Undo
This function is used to undo a move and go to previous position. In “undo”,we traverse the linked list using a ‘temp’ pointer, then following . We make temp point to the previous game state, and then pnext of previous node will be made pointed to null.In this way, Undo is implemented.

## Review
The review function reviews the game from beginning, i.e, displays all gamestates sequentially till the current gamestate.

## Future moves
This function lets you look into the all the possible moves into the future for the next k moves.



# USER-GUIDE  
## INSTRUCTIONS ON HOW TO PLAY CHECKERS ON TERMINAL 

You need to compile game.c , mainmenu.c ,Undo_Review.c, future_moves.c(i.e, 4 files) together to get a .out file.Then run it by giving ./a.out.
The interface of game displays details about current gamestate like current player , i th number of turn, current gamestate board.
It asks for a command--(“Enter a command”)
Write/give one of the following commands on terminal-
## Move: (“move” /  “m” - you can give any of the two commands)
When you type this command, it asks for the coordinates of the piece you want to move. Now give the coordinates in the following way
``current_X  current_Y target_X  target_Y``
According to your move, a command pops up describing your move like “Regular move”, “you made a capture”, “invalid move”.
## Undo: (“undo”/ “u”): 
This changes current gamestate to previous gamestate. Everytime you “undo”, gamestate gets changed to the previous one.
## Review: (“review”/ “r”):
As the name suggests, this displays the gamestates from beginning till the current gamestate.
## Future moves:(“future”/ “f”) 
When you give the command (“future”/ “f”),you need to enter ‘X’ , which is the number of moves into the future you wish to see.
The function then prints every possible configuration of the board after ‘x’ moves. As mentioned in the project requirements, EACH players turn counts as 1 move, so a round of red then black counts as 2.
## Reset: (“reset”/ “R”/ “ff”)
If this command is given (“reset”/ “R”/ “ff”) it once again asks to reset or not. By giving “Y” (yes)( it doesn’t reset if you give “n”), it resets the game and now both players can start a fresh game.



