#ifndef board_h
#define board_h

#include <string>
#include <gmpxx.h>

// sudoku doesn't have to be 3x3, so let's explicitly code it with that in mind.
// we'll start with 2x3 and go from there. 
// X X X Y Y Y
// X X X Y Y Y
// Y Y Y X X X
// Y Y Y X X X
// X X X Y Y Y
// X X X Y Y Y

#define board_sizeA 3
//#define board_sizeB 2
#define board_sizeB 3
#define board_numberOfOptions (board_sizeA*board_sizeB)
#define board_squaresPerRow board_sizeB
#define board_squaresPerColumn board_sizeA
#define board_height (board_squaresPerColumn*board_sizeB)
#define board_width (board_squaresPerRow*board_sizeA)
#define board_bitsetWidth (board_height*board_width)

class Board {
    private:
        mpz_class possibilities[board_numberOfOptions+1]; // I will be 1 indexing with 0 as filled or not (1 is still looking, 0 has assigned)
        short board[board_height][board_width]; // this stores the actual data
        void emptyBoard();
    
    public:
        Board();
        Board(short input[board_height][board_width]);
        Board(std::string numbers);
        int updateBoard(size_t row, size_t col, int value); //return 0 if illegal
        std::string toString();
        std::string toString(int index);
        int isDone();
        int solve();
        void printMasks();
        std::string toStringMask(mpz_class num);
        int getRow(mpz_class board);
        int getCol(mpz_class board);
        int getSquareRow(mpz_class board);
        int getSquareCol(mpz_class board);
        int checkBoardIsLegal();
        mpz_class getFirstBit(mpz_class board);
        int pickFirstEmpty();


};

#endif

