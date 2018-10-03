/*
=============================================================================================
Name: hw6prgrm.h
Author: Gabriel Castro
GUID: gmc0094
Email: GabrielCastro@my.unt.edu
Description: This is the header file containing all functin declarations, include directives,
             enumerated types, global constants, etc.. for the Stratego game.
=============================================================================================
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Global Variables
enum Rank { FLAG = 'F', BOMB = 'B', 
             MARSHAL = '1', GENERAL = '2', 
             COLONEL = '3', MAJOR = '4',
             CAPTAIN = '5', LIEUTENANT = '6',
             SERGEANT = '7', MINER = '8',
             SPY = '9', EMPTY = ' ' };
enum Color { BLUE = 'B', RED = 'R', NONE = 'N'};
const int SIZE = 5; // Size of the board
struct Piece {
    Rank rank;
    Color color;
    bool moveable;   
};

// Declaring functions
void printHeader(); // Prints the header containing the department, course number, name, guID, and email
void printRules(); // Prints the rules for the game and information about the game board
void initializeBoard(Piece **board, int s); // Initializes the boards to a default value
void assignPieces(Piece **board, int s); // Assigns the pieces to the board
bool pieceAt(int y, int x, Piece **board); // Determines if there is a piece at given position
int random(int s, int e); // Generates a random number between the range, inclusively
Rank getRank(int p); // Returns the rank specified by the int
void printBoard(Piece **board, int s, bool reveal); // Prints the board to the console
void addPiece(Piece **board, Rank pb, Rank pr); // Adds the piece on the board
int getY(string pos); // Gets the Y position of piece in the board with (0(y),0(x)) being the upper left corner.
int getX(string pos); // Gets the X position of piece in the board with (0(y),0(x)) being the upper left corner.
bool canMove(Piece **board, string pos); // Returns whether the piece at the position can move
bool validMove(Piece **board, string sp, string ep); // Returns whether the desired move is valid
bool updateBoard(Piece **board, string sp, string ep); // Updates the board and returns if the game is over
int getValue(int p); // Returns the value of the passed in Rank
bool canDestroy(Rank r1, Rank r2); // Determines if the first piece can destroy the second