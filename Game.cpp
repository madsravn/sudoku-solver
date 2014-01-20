#include <iostream>
#include "Game.hpp"

Game::Game(int gamesize):size(gamesize) {

}


Game::Game() {
    size = 9;
}

void Game::Load(const std::string& filename) {
    // Load the game into the game vector
}

void Game::Print() {
    for(int i = 0; i < entries.size(); ++i) {
        if(i > 0 && i%size == 0) {
            std::cout << std::endl;
        }
        std::cout << entries.at(i) << " ";
    }
}

void Game::Solve() {
    // Find a solution to the game
    

}
