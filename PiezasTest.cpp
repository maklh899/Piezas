/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/******** Testing Constructor ********/

//every piece should be blank
TEST(PiezasTest, construct_blank_board)
{
    Piezas board;
    for (int i=0; i < BOARD_ROWS; ++i){
        for (int j=0; j < BOARD_COLS; ++j){
            ASSERT_EQ(board.pieceAt(i,j), Blank);
        }
    }
}

/* ----- Testing reset ----- */

// resets game after 3 turns & checks for blanks
TEST(PiezasTest, reset_three_turns)
{
    Piezas board;
    // x
    board.dropPiece(0);
    // o
    board.dropPiece(2);
    // x
    board.dropPiece(3);
    // reset game
    board.reset();
    EXPECT_EQ(Blank, board.pieceAt(0,0));
}

/******** Testing Drop Piece ********/

// out of bounds in negative range
TEST(PiezasTest, dp_out_of_bounds_neg)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.dropPiece(-5));
}

// out of bounds in positive range
TEST(PiezasTest, dp_out_of_bounds_pos)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.dropPiece(5));
}

// one turn and returns x
TEST(PiezasTest, dp_drop_one)
{
    Piezas board;
    ASSERT_EQ(board.dropPiece(0), X);
}

// two turns and returns o
TEST(PiezasTest, dp_drop_two)
{
    Piezas board;
    board.dropPiece(1);
    ASSERT_EQ(board.dropPiece(1), O);
}

// two turns in same col and returns o
TEST(PiezasTest, dp_twice_same_col)
{
    Piezas board;
    board.dropPiece(0);
    ASSERT_EQ(board.dropPiece(0), O);
}

// have a full col and drop, return blank
TEST(PiezasTest, dp_four_col)
{
    Piezas board;
    board.dropPiece(3);
    board.dropPiece(3);
    board.dropPiece(3);
    ASSERT_EQ(board.dropPiece(3), Blank);
}

// have a full col and drop, return blank, next turn should be x
TEST(PiezasTest, dp_four_col_lost_turn)
{
    Piezas board;
    //x
    board.dropPiece(3);
    //o
    board.dropPiece(3);
    //x
    board.dropPiece(3);
    //o
    board.dropPiece(3);
    //x
    ASSERT_EQ(board.dropPiece(1), X);
}

// out of bounds, next turn shouldnt be the same person
TEST(PiezasTest, dp_out_of_bounds_losy_turn_sad)
{
    Piezas board;
    board.dropPiece(5);
    ASSERT_EQ(board.dropPiece(5), X);
}

/******** Testing Piece At********/

// returns X after one turn
TEST(PiezasTest, pa_one_turn)
{
    Piezas board;
    board.dropPiece(0);
    EXPECT_EQ(X, board.pieceAt(0,0));
}

// returns X after 2 turns - shouldnt pass
TEST(PiezasTest, pa_sad_two_turn)
{
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(3);
    EXPECT_EQ(X, board.pieceAt(0,3));
}

// returns X after 3 turns
TEST(PiezasTest, pa_three_turn)
{
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(2);
    board.dropPiece(3);
    EXPECT_EQ(X, board.pieceAt(0,3));
}

// returns Invalid when given out of bounds coordinates pos
TEST(PiezasTest, pa_out_of_bound_pos_row_row)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.pieceAt(5,0));
}

// returns Invalid when given out of bounds coordinates neg
TEST(PiezasTest, pa_out_of_bound_pos_neg_row)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.pieceAt(-5,0));
}

// returns Invalid when given out of bounds coordinates neg
TEST(PiezasTest, pa_out_of_bound_neg_col)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.pieceAt(0,-5));
}

// returns Invalid when given out of bounds coordinates pos
TEST(PiezasTest, pa_out_of_bound_pos_col)
{
    Piezas board;
    EXPECT_EQ(Invalid, board.pieceAt(0,5));
}

// returns blank after one turn
TEST(PiezasTest, pa_one_turn_blank)
{
    Piezas board;
    board.dropPiece(0);
    EXPECT_EQ(Blank, board.pieceAt(2,1));
}

/******** Testing gameState() ********/

// returns invalid on an empty board
TEST(PiezasTest, gs_empty_board)
{
    Piezas board;
    ASSERT_EQ(board.gameState(), Invalid);
}

// returns invalid on an unfinisehed board
TEST(PiezasTest, gs_partial_board)
{
    Piezas board;
    board.dropPiece(1);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(2);
    board.dropPiece(3);
    ASSERT_EQ(board.gameState(), Invalid);
}

// returns horizontal winner x
TEST(PiezasTest, gs_x_row_winner)
{
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(0);
    board.dropPiece(3);
    board.dropPiece(3);
    board.dropPiece(1);
    board.dropPiece(2);
    ASSERT_EQ(board.gameState(), X);
}

// returns vertical winner x
TEST(PiezasTest, gs_x_col_winner)
{
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(0);
    board.dropPiece(2);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(3);
    board.dropPiece(3);
    ASSERT_EQ(board.gameState(), X);
}

// returns horizontal winner o random
TEST(PiezasTest, gs_x_row_winner_2){
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(3);
    board.dropPiece(0);
    board.dropPiece(0);
    board.dropPiece(1);
    ASSERT_EQ(board.gameState(), O);
}

// return Blank no winner
TEST(PiezasTest, gs_no_winner)
{
    Piezas board;
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(1);
    board.dropPiece(0);
    board.dropPiece(0);
    board.dropPiece(1);
    board.dropPiece(2);
    board.dropPiece(2);
    board.dropPiece(3);
    board.dropPiece(3);
    ASSERT_EQ(board.gameState(), Blank);
}