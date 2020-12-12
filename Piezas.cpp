#include "Piezas.h"
#include <vector>
#include <cmath>
#include <iostream>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    //turn starts with X
    turn = X;

    //resize the board to be 3x4
    board.resize(BOARD_ROWS);
    for(int i=0; i < (int)board.size(); ++i)
        board[i].resize(BOARD_COLS);

    //setting board to blank
    for(int i=0; i<BOARD_ROWS; ++i)
        for(int j=0; j<BOARD_COLS; ++j)
            board[i][j] = Blank;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    //turn starts with X
    turn = X;

    //resize the board to be 3x4
    board.resize(BOARD_ROWS);
    for(int i=0; i < (int)board.size(); ++i)
        board[i].resize(BOARD_COLS);

    //setting board to blank
    for(int i=0; i<BOARD_ROWS; ++i)
        for(int j=0; j<BOARD_COLS; ++j)
            board[i][j] = Blank;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    std::cout<<"\n-----DropPiec()-----\n";

    //checking for out of bounds
    if(column >= BOARD_COLS || column < 0)
    {
        //person loses turn
        if(turn == X)
            turn = O;
        else
            turn = X;

        std::cout<<"col out of bounds ->\tturn = "<<turn<<"\n";
        //return Invalid
        return Invalid;
    }

    //checking if column is full 
    // - checks the col row if populated
    std::cout<<"____column full___\n";
    int full_col = 0;
    for(int i = BOARD_ROWS-1; i >= 0; --i)
    {   
        std::cout<<"Top place: board["<<i<<"]["<<column<<"] = "<<board[i][column]<<std::endl;
        if(board[i][column] == X || board[i][column] == O)
        {
            full_col++;
        }
    }

    //returns blank if column is full
    if(full_col==3)
    {
        //person loses turn
        if(turn == X)
            turn = O;
        else
            turn = X;

        std::cout<<"\tturn = "<<turn<<"\n";
        //return Invalid
        return Blank;
    }
     std::cout<<"____column full end___\n";


    //looking for the next empty place in the column
    // - checks bottom to top
    std::cout<<"____next empty space___\n";
    for(int i = 2;i >= 0; --i)
    {
        if(board[i][column] == Blank)
        {
            //places current person's piece
            board[i][column] = turn;
            
            // chenges player's turn
            if(turn == X)
                turn = O;
            else
                turn = X;

            std::cout<<"____next empty space end___\n";
            //returns what piece is placed
            return board[i][column];
        }
    }

    return Invalid;

}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    // Invert row
    row = abs(row - 2);

    if ((row >= BOARD_ROWS || row < 0 ) || ( column >= BOARD_COLS || column < 0))
    {
        return Invalid;
    }
    //should return Blank or the Piece
    return board[row][column];

}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    std::cout<<"\n-----gameState()-----\n";

    // Check if board is full
    std::cout<<"____board is full___\n";
    bool full_board = true;
    for(int i = 0;i < (int)board.size(); ++i)
    {
        for(int j = 0;j < (int)board[i].size(); ++j)
        {
            if(board[i][j] == Blank)
            {
                full_board = false;
            }
        }
    }
   

    //if the board is full check for a winner
    if(!full_board)
    {
        std::cout<<"____board is full end___\n";
        return Invalid;
    }
        

    // searches horizontally for the max streak
    int x_max, o_max, running_total = 0;

    std::cout<<"____search horizontal___\n";
    for(int j = 0; j < 4 ; ++j)
    {
        for(int i = 0; i < 2; ++i)
        {
            // Count streaks, checks if the cur is equal to the previous
            if(board[i][j] == board[i+1][j])
            {
                running_total++;

                //checks the piece and if the running streak is greater
                //that pieces max streak, assign the piece_max with the running total
                if(board[i][j] == X && running_total > x_max) 
                    x_max = running_total;
                else if(board[i][j] == O && running_total > o_max) 
                    o_max = running_total;
            }
            else
            {
                running_total = 0;
            }
        }
    }
    std::cout<<"____search horizontal end___\n";


    std::cout<<"____search vertical___\n";
    std::cout<<"board size: "<<board.size()<<std::endl;
    for(int i = 0; i < (int)board.size(); ++i)
    {
        for(int j = 0; j < (int)board.size(); ++j)
        {
            // Count streaks, checks if the cur is equal to the previous
            if(board[i][j] == board[i][j+1])
            {
                running_total++;

                //checks the piece and if the running streak is greater
                //that pieces max streak, assign the piece_max with the running total
                if(board[i][j] == X && running_total > x_max) 
                    x_max = running_total;
                else if(board[i][j] == O && running_total > o_max) 
                    o_max = running_total;
            }
            else
            {
                running_total = 0;
            }
        }
    }
    std::cout<<"____search vertical end___\n";
    //retrun blank if theres a tie
    if(x_max == o_max) 
        return Blank;
    else if(x_max > o_max)
        return X;
    else 
        return O;

    
}