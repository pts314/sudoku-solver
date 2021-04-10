#include "board.hpp"

Board::emptyBoard() {
    for (size_t i = 0; i <= board_numberOfOptions; i++) {
        possibilities[i].set();
    }
    for (size_t i = 0; i < board_hieght*board_width; i++) {
        board[i] = 0;
    }
}

Board::Board() {
    emptyBoard();
}

Board::Board(short input[board_hieght][board_width]) {
    emptyBoard();
    for (size_t i = 0; i < board_hieght; i++) {
        for (size_t j = 0; j < board_width; j++) {
            if (input[i][j]) {
                updateBoard(i,j,input[i][j]);
            }
        }
    }
}

Board::updateBoard(size_t row, size_t col, int value) {
    //update row
    possibilities[value] &= ~(maskRow<<(row*board_width));
    //update col
    possibilities[value] &= ~(maskCol<<col);
    //update square
    size_t squareRow = row/board_sizeB;
    size_t squareCol = col/board_sizeA;
    possibilities[value] &= ~(maskBox<<(squareRow*board_sizeB*board_width+squareCol*board_sizeA))
    //claim the spot on the first board
    possibilities[0].set(row*board_width+col,0);
    //update all boards
    for (size_t i = 1; i < board_numberOfOptions; i++) {
        possibilities[i] &= possibilities[0];
    }
    //update lazy board
    board[row][col] = value;
}
    
    
