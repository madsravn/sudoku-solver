#include "Game.hpp"
#include <iostream>


int main() {
    // Let's play a game of sudoku
    
    Game g;
    g.Load("game2.txt");
    g.Print();

    g.Solve();
    
    
    return 0;
}
