#include "Game.hpp"
#include <iostream>


int main() {
    // Let's play a game of sudoku
    
    Game g;
    g.Load("game3.txt");
    g.Print();

    //g.Solve();

    //g.Print();
    
    auto solutions = g.GetSolutions();
    std::cout << solutions.size() << std::endl;
    
    return 0;
}
