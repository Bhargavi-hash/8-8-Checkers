# 8-8-Checkers

Checkers (also known as Draughts) is a popular group
of board games. The most commonly played one is an
8x8 version of American Checkers (also known as En-
glish Draughts). Here, we will be developing a terminal
version of this game.

# Features

1) A feature to UNDO as many moves as asked by the
   players (provided both players agree).
2) A feature to REVIEW the game from the start, so
   the players can see what led to the current game
   state if they wish to.
3) A feature to SHOW ALL POSSIBLE MOVES for
   the next k turns (if both players make a move each,
   that is counted as two turns), where k is a number
   that the player gives.
# Checker Board Numbering

![Untitled drawing (1)](https://user-images.githubusercontent.com/82858718/115345071-e22d8880-a1cb-11eb-8a60-6e8ed9e0abe8.png)


# Checker-board RULES

1) Each player starts with 12 men on the dark squares of the 3 rows nearest to that players side.
2) Each player is assinged a different color.
3) The men of each player can move only in the dark squares and only diagnol moves are possible.
4) The row closest to each player is called the kings row or crownhead.
5) The player with the darker-coloured pieces moves first. Then plays the second player.
# Move Rules
There are two different ways to move in English draughts:

Simple move: 

A simple move consists of moving a piece one square diagonally to an adjacent unoccupied dark square. Uncrowned pieces can move diagonally forward only; kings can move in any diagonal direction.

Jump: 

A jump consists of moving a piece that is diagonally adjacent an opponent's piece, to an empty square immediately beyond it in the same direction (thus "jumping over" the opponent's piece front and back ). Men can jump diagonally forward only; kings can jump in any diagonal direction. A jumped piece is considered "captured" and removed from the game. Any piece, king or man, can jump a king.
NOTE: 

If a player has the option to jump, he must take it, even if doing so results in disadvantage for the jumping player. 
