/*
======================================================================================
Name: hw6main.cpp
Author: Gabriel Castro
GUID: gmc0094
Email: GabrielCastro@my.unt.edu
Description: This program will enable a user to play a simplified version of Stratego.
======================================================================================
*/

#include "hw6prgm.h" // The program header file

int main()
{
    srand(time(NULL));

    printHeader(); 
    printRules();         

    // The board
    Piece **board;
    board = new Piece*[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
        board[i] = new Piece[SIZE];
    }

    initializeBoard(board, SIZE);
    assignPieces(board, SIZE);
    
    string sp = ""; // The starting position of the move
    string ep = ""; // The ending position of the move
    
    do
    {
        printBoard(board, SIZE, false);
        do
        {
            cout << "RED MOVE: Enter current coordinates of the piece (e.g. D2) or QQ to quit: ";
            cin >> sp;
        }while(!canMove(board, sp)); // canMove will display error message

        if(sp != "QQ")
        {
            do
            {
                cout << "RED MOVE: Enter the new coordinates of the piece at " << sp << ": ";
                cin >> ep;
            }while(!validMove(board, sp, ep)); // validMove will display error message
        }
    }while(!updateBoard(board, sp, ep));

    if(sp != "QQ")
    {
        cout << "RED " << (char)board[getY(ep)][getX(ep)].rank << " at " << sp << " captured BLUE flag at " << ep << ". Congratulations!" << endl;
    }else
    {
        cout << "RED player forfieted." << endl;
    }

    printBoard(board, SIZE, true);

    return 0;
}