/*
=============================================================================================
Name: hw6func.cpp
Author: Gabriel Castro
GUID: gmc0094
Email: GabrielCastro@my.unt.edu
Description: This is the cpp file containing all functin definitions for the hw6prgrm.h file.
=============================================================================================
*/

#include "hw6prgm.h"

/*
 =======================================================================
 Function: printHeader
 Parameters: none
 Return: void
 Description: This function prints the header containing the department,
	      course number, name, guID, and email.
 =======================================================================
*/
void printHeader()
{
	/* The following outputs a nicely formatted message displaying my name, EUID, and UNT email. */
	cout << "+-------------------------------------------------------+\n";
	cout << "|             Computer Science and Engineering          |\n";
	cout << "|              CSCE 1030 - Computer Science 1           |\n";
	cout << "|  Gabriel Castro   gmc0094   GabrielCastro@my.unt.edu  |\n";
	cout << "+-------------------------------------------------------+\n\n";
}


/*
 =======================================================================
 Function: printRules
 Parameters: none
 Return: void
 Description: This function prints out the rules of the game to the user
 =======================================================================
*/
void printRules()
{
    cout << "W e l c o m e   t o   1030   S t r a t e g o" << endl;
    
    cout << "------------------------------------------------------------------------" << endl;
    cout << "This program will set up a 5x5 game board for a 1030 version of the game" << endl;
    cout << "of Stratego. One player will compete against the computer, each assigned" << endl;
    cout << "10 total pieces consisting of the following:" << endl;
    cout << " 1 FLAG (F)" << endl;
    cout << " 3 BOMB (B)" << endl;
    cout << " 1 MARSHAL (1) or GENERAL (2)" << endl;
    cout << " 3 COLONEL (3), MAJOR (4), CAPTAIN (5), LIEUTENANT (6), or SERGEANT (7)" << endl;
    cout << " 1 MINER (8)" << endl;
    cout << " 1 SPY (S)" << endl;
    cout << endl;
    cout << "GENERAL RULES:" << endl;
    cout << "--------------" << endl;
    cout << "For the most part, the game will follow the standard Stratego rules, although" << endl;
    cout << "there are some exceptions." << endl;
    cout << "1. Both players (BLUE and RED) will have all of their 10 game pieces as-" << endl;
    cout << " signed randomly with the only requirement being that the FLAG must be" << endl;
    cout << " placed in the back row. RED will start the game first." << endl;
    cout << "2. Higher ranked pieces can capture lower ranked pieces in the following" << endl;
    cout << " order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> S, meaning that 1 (the" << endl;
    cout << " MARSHAL) can remove 2 (the GENERAL) and so forth. The MINER (8) piece" << endl;
    cout << " may strike a BOMB and remove it to occupy the now unoccupied space. A" << endl;
    cout << " SPY (S), although the lowest ranked piece, may remove the MARSHAL (1)" << endl;
    cout << " or the GENERAL (2). When pieces have equal rank, then both pieces are removed." << endl;
    cout << "3. The FLAG and BOMBs are not moveable while all of the other pieces may" << endl;
    cout << " move one square at a time forward, backward, or sideward, but not di-" << endl;
    cout << " agonally to an open square." << endl;
    cout << "4. A player must either move or strike on his/her turn." << endl;
    cout << "5. The game ends when a player strikes his/her opponent's flag." << endl;
    cout << "------------------------------------------------------------------------" << endl;
}


/*
 =======================================================================
 Function: initializeBoard
 Parameters: a 2d dynamic array representing the board
             an int representing the size of the array 
             (eg. width or height)
 Return: void
 Description: This function initializes the values of each array index
              to a default value, EMPTY for the Piece matrix and NONE
              for the Color matrix.
 =======================================================================
*/
void initializeBoard(Piece **board, int s)
{
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
        {
            board[i][j].rank = EMPTY;
            board[i][j].color = NONE;
            board[i][j].moveable = false;
        }
    }
}


/*
 =======================================================================
 Function: assignPieces
 Parameters: a 2d dynamic array representing the board
             an int representing the size of the array 
             (eg. width or height)
 Return: void
 Description: This function assigns pieces to the board as determined by
              the Stratego rules.
 =======================================================================
*/
void assignPieces(Piece **board, int s)
{
    // Setting the color
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
        {
            if(i <= 1)
            {
                board[i][j].color = BLUE;
            }
            if(i >= 3)
            {
                board[i][j].color = RED;
            }
        }
    }

    // Randomly assigning the flags on the first row of each team
    int x = random(0,4);
    board[0][x].rank = FLAG; // Team blue
    board[0][x].moveable = false;
    board[4][random(0,4)].rank = FLAG; // Team red

    // Randomly assigning the bombs on the first two rows of each team
    for(int i = 0; i < 3; i++)
    {
        addPiece(board, BOMB, BOMB);
    }

    // Randomly assigning either a Marshall or General to one of the two back rows for each team
    addPiece(board, getRank(random(1,2)), getRank(random(1,2)));

    // Randomly assigning a Miner to one of the two back rows for each team
    addPiece(board, MINER, MINER);
    

    // Randomly assigning a Spy to one of the two back rows for each team
    addPiece(board, SPY, SPY);    

    // Randomly assigning either a Colonel, Major, Captain, Lieutenant, or Sargent on the first two rows of each team
    for(int i = 0; i < 3; i++)
    {
        addPiece(board, getRank(random(3,7)), getRank(random(3,7)));
    }

    // Setting the pieces for as either movable or not
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
        {
            if(board[i][j].rank == FLAG || board[i][j].rank == BOMB || board[i][j].rank == EMPTY)
            {
                board[i][j].moveable = false;
            }else
            {
                board[i][j].moveable = true;
            }
        }
    }
}


/*
 =======================================================================
 Function: random
 Parameters: int for the starting value of the range
             int for the ending value of the range
 Return: int
 Description: This function generates a random integer within the given
              range. (inclusively)
 =======================================================================
*/
int random(int s, int e)
{
    int y = (e - s) + 1;
    int num = (rand() % y) + s;
    return num;
}


/*
 =======================================================================
 Function: pieceAt
 Parameters: int representing y coordinate on the board
             int representing the x coordinate on the board
 Return: bool
 Description: This function determines if a piece is already at the
              specified location.
 =======================================================================
*/
bool pieceAt(int y, int x, Piece **p)
{
    return !(p[y][x].rank == EMPTY);
}


/*
 ========================================================================
 Function: getRank
 Parameters: int representing the value of the Rank enum
 Return: Rank
 Description: This function returns the corresponding enum Rank value
              for the passed in integer. (ex: input of 3 returns Colonel)
 ========================================================================
*/
Rank getRank(int p)
{
    switch(p)
    {
        case 1:
            return MARSHAL;
        case 2:
            return GENERAL;
        case 3:
            return COLONEL;
        case 4:
            return MAJOR;
        case 5:
            return CAPTAIN;
        case 6:
            return LIEUTENANT;
        case 7:
            return SERGEANT;
        case 8:
            return MINER;
        case 9:
            return SPY;
        default:
            return EMPTY;
    }
}


/*
 ========================================================================
 Function: getValue
 Parameters: Rank value
 Return: int
 Description: This function returns the corresponding value for the given
              Rank. (ex: input of Colonel returns 3)
 ========================================================================
*/
int getValue(int p)
{
    switch(p)
    {
        case MARSHAL:
            return 1;
        case GENERAL:
            return 2;
        case COLONEL:
            return 3;
        case MAJOR:
            return 4;
        case CAPTAIN:
            return 5;
        case LIEUTENANT:
            return 6;
        case SERGEANT:
            return 7;
        case MINER:
            return 8;
        case SPY:
            return 9;
        default:
            return 0;
    }
}


/*
 =======================================================================
 Function: printBoard
 Parameters: A 2d dynamic Piece array representing the board
             an int representing the size of the array 
             (eg. width or height)
             a bool value to specifiy if we want to reveal the blue 
             players pieces.
 Return: void
 Description: This function prints out the board to the console, pieces
              are printed out with colors corresponding to Color matrix
              array.
 =======================================================================
*/
void printBoard(Piece **board, int s, bool reveal)
{
    cout << "    1 2 3 4 5" << endl;
    cout << "  +-----------+" << endl;

    for(int i = 0; i < s; i++)
    {
        cout << static_cast<char>(i + 65) << " | ";

        for(int j = 0; j < s; j++)
        {
            if(board[i][j].color == BLUE)
            {
                if(reveal)
                {
                    if(board[i][j].rank == FLAG)
                    {
                        printf("\033[1;33m%c \033[0m", static_cast<char>(board[i][j].rank));    
                    }else
                    {
                        printf("\033[1;34m%c \033[0m", static_cast<char>(board[i][j].rank));    
                    }           
                }else
                {
                   printf("\033[1;34m%c \033[0m", static_cast<char>('X'));                
                }
            }else if(board[i][j].color == RED)
            {
                printf("\033[1;31m%c \033[0m", static_cast<char>(board[i][j].rank));                                
            }else if(board[i][j].color == NONE)
            {
                cout << "  ";
            }
        }

        cout << "|" << endl;
    }

    cout << "  +-----------+" << endl;  
}


/*
 =======================================================================
 Function: addPiece
 Parameters: a 2d dynamic array representing the board
             a Rank, the Rank to add to the blue team
             a Rank, the Rank to add to the red team
             (eg. width or height)
 Return: void
 Description: This function assigns the given pieces to the board.
              Randomly in the first two rows of each team and will only
              assign it to a position if the position is empty.
 =======================================================================
*/
void addPiece(Piece **board, Rank pb, Rank pr)
{
    int y = random(0,1);
    int x = random(0,4);
    // Checks if piece alread at specified position on board, if so new position is found
    while(pieceAt(y, x, board))
    {
        y = random(0,1);
        x = random(0,4);
    }
    board[y][x].rank = pb; // Adding piece

    y = random(3,4);
    x = random(0,4); 
    // Checks if piece alread at specified position on board, if so new position is found
    while(pieceAt(y, x, board))
    {
        y = random(3,4);
        x = random(0,4);
    }
    board[y][x].rank = pr; // Adding piece
}


/*
 ===========================================================================
 Function: getY
 Parameters: string representing the game board coordinates
 Return: int
 Description: This function returns the Y position of the piece in the board 
              with (0(y),0(x)) being the upper left corner.
 ===========================================================================
*/
int getY(string pos)
{
    return (static_cast<int>(pos[0]) - 65); // ASCII value of A is 65
}


/*
 ===========================================================================
 Function: getX
 Parameters: string representing the game board coordinates
 Return: int
 Description: This function returns the X position of the piece in the board 
              with (0(y),0(x)) being the upper left corner.
 ===========================================================================
*/
int getX(string pos)
{
    return (static_cast<int>(pos[1]) - 49); // ASCII value of 1 is 49
}


/*
 ===================================================================
 Function: canMove
 Parameters: string representing piece coordinate
 Return: boolean
 Description: This function determines if the piece at the specified
              coordinate can be moved.
 ===================================================================
*/
bool canMove(Piece **board, string pos)
{
    if(pos == "QQ") // Forfeiting
    {
        return true;
    }

    if(pos.length() == 2) // Checking if the coordinate is valid
    {
        int yx[] = {getY(pos), getX(pos)};

        if(yx[0] < 0 || yx[0] > 4) // Checking if the row is valid
        {
            cout << "The coordinate " << pos << " is not valid (invalid row)." << endl;
            return false;
        }
        if(yx[1] < 0 || yx[1] > 4) // Checking if the collumn is valid
        {
            cout << "The coordinate " << pos << " is not valid (invalid collumn)." << endl;
            return false;
        }

        if(board[yx[0]][yx[1]].moveable == false) // Checking if the piece is moveable
        {
            cout << "The piece at " << pos << " is not moveable." << endl;
            return false;
        }else // Checking if the piece has any valid moves
        {
            int y = yx[0];
            int x = yx[1] - 1;

            if(!(x < 0))
            {
                if(board[y][x].rank == EMPTY)
                {
                    return true;
                }

            }

            x += 1;
            y -= 1;
            if(!(y < 0))
            {
                if(board[y][x].rank == EMPTY)
                {
                    return true;
                }
            }

            y += 2;
            if(!(y > 4))
            {
                if(board[y][x].rank == EMPTY)
                {
                    return true;
                }
            }

            x += 1;
            y -= 1;
            if(!(x > 4))
            {
                if(board[y][x].rank == EMPTY)
                {
                    return true;
                }
            }

            cout << "No valid moves available for the piece at " << pos << "." << endl;
            return false;
        }
    }else
    {
        cout << "The coordinate " << pos << " is not valid." << endl;
        return false;
    }
}


/*
 ====================================================================
 Function: validMove
 Parameters: a 2d dynamic array representing the board
             string representing the piece's starting coordinate
             string representing the piece's ending coordinate
 Return: boolean
 Description: This function determines if the specified move is valid
 ====================================================================
*/
bool validMove(Piece **board, string sp, string ep)
{

    int sc[] = {getY(sp), getX(sp)};
    int ec[] = {getY(ep), getX(ep)};

    if(board[ec[0]][ec[1]].color == RED) // Checks if the place to move is occupied by 
    {
        return false;
    }

    if((abs(ec[0]-sc[0]) + abs(ec[1] - sc[1]) - 1))
    {
        cout << "That is not a valid move" << endl;
    }

    return !(abs(ec[0]-sc[0]) + abs(ec[1] - sc[1]) - 1); // If valid move then result is 0 == false, !false == true
}


/*
 ====================================================================
 Function: updateBoard
 Parameters: a 2d dynamic array representing the board
             string representing the piece's starting coordinate
             string representing the piece's ending coordinate
 Return: boolean
 Description: This function updates the board and returns if the game
              is over.
 ====================================================================
*/
bool updateBoard(Piece **board, string sp, string ep)
{
    int sc[] = {getY(sp), getX(sp)};
    int ec[] = {getY(ep), getX(ep)};

    if(sp == "QQ") // If the user has forfieted
    {
        return true;
    }

    if(board[ec[0]][ec[1]].rank == FLAG) // If the Flag is the end destination (captured)
    {
        return true;
    }

    if(board[ec[0]][ec[1]].rank == EMPTY) // If the destination is empty
    {
        cout << "RED " << (char)board[sc[0]][sc[1]].rank << " moves from " << sp << " to " << ep << endl; // Telling user the move

        // Updating board
        board[ec[0]][ec[1]].rank = board[sc[0]][sc[1]].rank;
        board[ec[0]][ec[1]].color = board[sc[0]][sc[1]].color;
        board[ec[0]][ec[1]].moveable = board[sc[0]][sc[1]].moveable;

        board[sc[0]][sc[1]].rank = EMPTY;
        board[sc[0]][sc[1]].color = NONE;
        board[sc[0]][sc[1]].moveable = false;

    }else // There is a piece on the destination
    {
        if(canDestroy(board[sc[0]][sc[1]].rank, board[ec[0]][ec[1]].rank)) // The piece moving can capture the piece at its destination
        {
            cout << "RED " << (char)board[sc[0]][sc[1]].rank << " at " << sp << " captures BLUE " << (char)board[ec[0]][ec[1]].rank << " at " << ep << endl;

            // Updating board
            board[ec[0]][ec[1]].rank = board[sc[0]][sc[1]].rank;
            board[ec[0]][ec[1]].color = board[sc[0]][sc[1]].color;
            board[ec[0]][ec[1]].moveable = board[sc[0]][sc[1]].moveable;

            board[sc[0]][sc[1]].rank = EMPTY;
            board[sc[0]][sc[1]].color = NONE;
            board[sc[0]][sc[1]].moveable = false;
        }else // The piece moving cannot capture the piece its moving to
        {
            if(board[ec[0]][ec[1]].rank == BOMB)
            {
                cout << "RED " << (char)board[sc[0]][sc[1]].rank << " at " << sp << " blown up by BLUE " << (char)board[ec[0]][ec[1]].rank << " at " << ep << endl;
            }else
            {
                cout << "RED " << (char)board[sc[0]][sc[1]].rank << " at " << sp << " captured by BLUE " << (char)board[ec[0]][ec[1]].rank << " at " << ep << endl;
            }

            board[sc[0]][sc[1]].rank = EMPTY;
            board[sc[0]][sc[1]].color = NONE;
            board[sc[0]][sc[1]].moveable = false;
        }
    }

    return false;
}


/*
 =====================================================================
 Function: canDestroy
 Parameters: the Rank of the first piece
             the Rank of the second piece
 Return: boolean
 Description: This function returns if the first piece can capture the
              second.
 =====================================================================
*/
bool canDestroy(Rank r1, Rank r2)
{
    if(r2 == BOMB)
    {
        if(r1 == MINER)
        {
            return true;
        }else
        {
            return false;
        }
    }

    if(r1 == SPY)
    {
        if(getValue(r2) <= 2) // General or Sergeant, Spy can kill them
        {
            return true;
        }else
        {
            return false;
        }
    }

    if(getValue(r1) < getValue(r2))
    {
        return true;
    }else
    {
        return false;
    }
}