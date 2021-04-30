#include "board.hpp"
#include <string>
#include <sstream>
#include <iostream>

mpz_class initGetMaskRow() {
    mpz_class value = -1;
    value<<=board_width;
    return ~value;
}

mpz_class initGetMaskCol() {
    mpz_class value = 0;
    mpz_class one = 1;
    for (size_t i = 0; i < board_bitsetWidth; i+=board_width) {
        value |= one<<i;
    }
    return value;
}
mpz_class initGetMaskBox() {
    mpz_class value = -1;
    value<<=board_sizeA;
    value = ~value;
    for (size_t i = 1; i < board_sizeB; i++) {
        value |= value<<board_width;
    }
    return value;
}

mpz_class initGetMaskBoard() {
    mpz_class value = 1;
    value<<=board_bitsetWidth;
    value -= 1;
    return value;
}


const mpz_class maskRow = initGetMaskRow();
const mpz_class maskCol = initGetMaskCol();
const mpz_class maskBox = initGetMaskBox();
const mpz_class maskBoard = initGetMaskBoard();

void Board::emptyBoard() {
    for (size_t i = 0; i <= board_numberOfOptions; i++) {
        possibilities[i] = 1;
        possibilities[i] <<= board_bitsetWidth;
        possibilities[i] = -1;
    }
    for (size_t i = 0; i < board_height; i++) {
        for (size_t j = 0; j < board_width; j++) {
            board[i][j] = 0;
        }
    }
}

Board::Board() {
    emptyBoard();
}

Board::Board(short input[board_height][board_width]) {
    emptyBoard();
    for (size_t i = 0; i < board_height; i++) {
        for (size_t j = 0; j < board_width; j++) {
            if (input[i][j]) {
                updateBoard(i,j,input[i][j]);
            }
        }
    }
}
Board::Board(std::string numbers) {
    std::stringstream ss(numbers);
    emptyBoard();
    for (size_t i = 0; i < board_height; i++) {
        for (size_t j = 0; j < board_width; j++) {
            int num = ss.get()-'0';
            if (num) {
                updateBoard(i,j,num);
            }
        }
    }
}

// expects that you'll give it only a single bit. otherwise will give the lowest bit
int Board::getRow(mpz_class board) {
    return mpz_scan1(board.get_mpz_t(),0)/board_width;
}
int Board::getCol(mpz_class board) {
    return mpz_scan1(board.get_mpz_t(),0)%board_width;
}
int Board::getSquareRow(mpz_class board) {
    size_t squareRow = getRow(board)/board_sizeB;
    return squareRow;
}

int Board::getSquareCol(mpz_class board) {
    size_t squareCol = getCol(board)/board_sizeA;
    return squareCol;
}

int Board::checkBoardIsLegal() {
    mpz_class spaces = 0;
    // or all planes together
    for (size_t i = 1; i <= board_numberOfOptions; i++) {
        spaces |= possibilities[i];
    }
    // possibilities[0] lists all blank spaces
    // spaces lists all squares with notes
    // if the two aren't the same, we have an empty space with no legal moves, and the board is invalid
    return (spaces == possibilities[0]);
}
        

int Board::updateBoard(size_t row, size_t col, int value) {
    mpz_class m_one = 1;
    //update row
    possibilities[value] &= ~(maskRow<<(row*board_width));
    //update col
    possibilities[value] &= ~(maskCol<<col);
    //update square
    size_t squareRow = row/board_sizeB;
    size_t squareCol = col/board_sizeA;
    possibilities[value] &= ~(maskBox<<(squareRow*board_sizeB*board_width+squareCol*board_sizeA));
    //claim the spot on the first board
    possibilities[0] &= ~(m_one<<(row*board_width+col));
    //ensure first board stays on the board
    possibilities[0] &= maskBoard;
    //update all boards
    for (size_t i = 1; i <= board_numberOfOptions; i++) {
        possibilities[i] &= possibilities[0];
    }
    //update lazy board
    board[row][col] = value;

    return checkBoardIsLegal();
}

void Board::printMasks() {
    std::cout << toStringMask(maskRow) << std::endl;
    std::cout << toStringMask(maskCol) << std::endl;
    std::cout << toStringMask(maskBox) << std::endl;
    std::cout << toStringMask(maskBoard) << std::endl;
    std::cout << maskBoard << std::endl;
}
    
    
std::string Board::toStringMask(mpz_class num) {
    std::ostringstream out;
    // make the row 
    out << "+";
    for (size_t i = 0; i < board_squaresPerRow; i++) {
        for (size_t j = 0; j < board_sizeA*2-1; j++) {
            out << "-";
        }
        out << "+";
    }
    out << std::endl;
    std::string rowLine = out.str();
    out.str("");
    for (size_t i = 0; i < board_height; i++) {
        if ((i % board_sizeB) == 0) {
            out << rowLine;
        }
        for (size_t j = 0; j < board_width; j++) {
            if ((j % board_sizeA) == 0) {
                out << "|";
            } else {
                out << " ";
            }
            mpz_class tmp = 1&(num >> (i*board_width + j));
            out << tmp.get_ui();
        }
        out << "|" << std::endl;
    }
    out << rowLine;
    return out.str();
}
    
std::string Board::toString() {
    std::ostringstream out;
    // make the row 
    out << "+";
    for (size_t i = 0; i < board_squaresPerRow; i++) {
        for (size_t j = 0; j < board_sizeA*2-1; j++) {
            out << "-";
        }
        out << "+";
    }
    out << std::endl;
    std::string rowLine = out.str();
    out.str("");
    for (size_t i = 0; i < board_height; i++) {
        if ((i % board_sizeB) == 0) {
            out << rowLine;
        }
        for (size_t j = 0; j < board_width; j++) {
            if ((j % board_sizeA) == 0) {
                out << "|";
            } else {
                out << " ";
            }
            out << board[i][j];
        }
        out << "|" << std::endl;
    }
    out << rowLine;
    return out.str();
}
std::string Board::toString(int index) {
    std::ostringstream out;
    // make the row 
    out << "+";
    for (size_t i = 0; i < board_squaresPerRow; i++) {
        for (size_t j = 0; j < board_sizeA*2-1; j++) {
            out << "-";
        }
        out << "+";
    }
    out << std::endl;
    std::string rowLine = out.str();
    out.str("");
    for (size_t i = 0; i < board_height; i++) {
        if ((i % board_sizeB) == 0) {
            out << rowLine;
        }
        for (size_t j = 0; j < board_width; j++) {
            if ((j % board_sizeA) == 0) {
                out << "|";
            } else {
                out << " ";
            }
            mpz_class tmp = 1&(possibilities[index] >> (i*board_width + j));
            out << tmp.get_ui();
        }
        out << "|" << std::endl;
    }
    out << rowLine;
    return out.str();
}

int Board::isDone() {
    if (possibilities[0] == 0) {
        // board is full, should go on to checking
        std::cout << "Hey Human, check if this is done" << std::endl; // AKA, I'm a stub
        std::cout << toString() << std::endl;
        return 1;
    } else {
        return 0;
    }
    return 0;
}

mpz_class Board::getFirstBit(mpz_class bitboard) {
    mpz_class returnValue = 1;
    returnValue <<= mpz_scan1(bitboard.get_mpz_t(),0);
    return returnValue;
    
}
    

int Board::pickFirstEmpty() {
    if (isDone()) {
        return 1;
    }
    mpz_class bit = getFirstBit(possibilities[0]);
    for (size_t i = 1; i <= board_numberOfOptions; i++) {
        if ((bit & possibilities[i]) != 0) {
            Board newBoard = Board(this->board);
            int isLegal = newBoard.updateBoard(getRow(bit),getCol(bit),i);
            if (isLegal) {
                isLegal = newBoard.solve();
                if (isLegal) {
                    return 1;
                }
            } else {
                ;
            }
        }
    }
    return 0;
}

int Board::solve() {
    if (isDone()) {
        return 1;
    }
    // do logics that are sure
    int changed = 1;
    while (changed) {
        changed = 0;
        // list of function pointers to rules or something
        // functions are allowed to alter board since they are garenteed to be correct, 
        // changed |= board.(function)()
    }
    if (isDone()) {
        return 1;
    } else {
        //logics didn't work, so we'll have to guess. 
        return pickFirstEmpty();
    }
    return 0;
}




