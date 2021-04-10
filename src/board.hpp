#ifndef board_h
#define board_h

// sudoku doesn't have to be 3x3, so let's explicitly code it with that in mind.
// we'll start with 2x3 and go from there. 
// X X X Y Y Y
// X X X Y Y Y
// Y Y Y X X X
// Y Y Y X X X
// X X X Y Y Y
// X X X Y Y Y

#define board_sizeA 3
#define board_sizeB 2
#define board_numberOfOptions (board_sizeA*board_sizeB)
#define board_squaresPerRow board_sizeB
#define board_squaresPerColumn board_sizeA
#define board_height (board_squaresPerColumn*board_sizeB)
#define board_width (board_squaresPerRow*board_sizeA)
#define board_bitsetWidth (board_height*board_width)

std::bitset<board_bitsetWidth> initGetMaskRow() {
    std::bitset<board_bitsetWidth> value;
    value.set();
    value<<=board_width;
    return ~value;
}

std::bitset<board_bitsetWidth> initGetMaskCol() {
    std::bitset<board_bitsetWidth> value;
    value.reset();
    for (size_t i = 0; i < board_bitsetWidth; i+=board_width) {
        value.set(i,1);
    }
    return value;
}
std::bitset<board_bitsetWidth> initGetMaskBox() {
    std::bitset<board_bitsetWidth> value;
    value.set();
    value<<=board_sizeB;
    value = ~value;
    for (size_t i = 1; i < board_sizeA; i++) {
        value |= value<<board_width;
    }
    return value;
}

const global std::bitset<board_bitsetWidth> maskRow = initGetMaskRow();
const global std::bitset<board_bitsetWidth> maskCol = initGetMaskCol();
const global std::bitset<board_bitsetWidth> maskBox = initGetMaskBox();


#include <bitset>
class Board {
    private:
        std::bitset<board_bitsetWidth> possibilities[board_numberOfOptions+1]; // I will be 1 indexing with 0 as filled or not (1 is still looking, 0 has assigned)
        short board[board_height][board_width]; // this stores the actual data
    
    public:
        int updateBoard(size_t row, size_t col, int value); //return 0 if illegal


}
#endif
