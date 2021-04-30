#include <iostream>
#include <fstream>
#include "solver.hpp"
#include "board.hpp"


void testAssign() {
    for (size_t i = 0; i < board_height; i++) {
        for (size_t j = 0; j < board_width; j++) {
            Board thing;
            thing.updateBoard(i,j,4);
            std::cout << thing.toString() << std::endl;
            std::cout << thing.toString(4) << std::endl;
        }
    }
}

void testBitShift() {
    Board thing;
    thing.updateBoard(2,4,1);
    std::cout << thing.toString(1) << std::endl;
}

void runTests() {
    std::cout << "start with test assign" << std::endl;
    testAssign();
    
    std::cout << "now reading puzzle" << std::endl;
    std::fstream in;
    //in.open("../puzzles/2x3.txt");
    in.open("../puzzles/2x3.txt");
    std::string line;
    std::getline(in,line);
    std::cout << "got line " << std::endl;
    std::cout << line;
    Board thing(line);
    std::cout << thing.toString() << std::endl;
    for (int i = 0; i <= 6; i++) {
        //std::cout << thing.toString(i) << std::endl;
        ;
    }
        
    thing.printMasks();
}

void solvePuzzle() {
    std::string line;
    std::fstream in;
    //in.open("../puzzles/2x3.txt");
    in.open("../puzzles/5.txt");
    while (std::getline(in,line)) {
        Board puzzle = Board(line);
        std::cout << "we have this puzzle" << std::endl;
        std::cout << puzzle.toString() << std::endl;
        std::cout << "in solve puzzle" << std::endl;
        puzzle.solve();
    }
    in.close();
    //puzzle.printMasks();
}

int main() {
    solvePuzzle();
    return 0;
}
