#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Game.hpp"


template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (const auto& elem : v)
    {
        os << " " << elem;
    }
    os << " ]";
    return os;
}


// Size describes what size one block has
// A normal sudoku has size 3: 3*3 blocks - 3 wide and 3 high
Game::Game(int gamesize):size(gamesize*gamesize) {

}


Game::Game() {
    size = 3*3;
}

void Game::Load(const std::string& filename) {
    // Load the game into the game vector
    std::ifstream file;
    file.open(filename);
    if(file.fail()) {
        std::cout << "Error encountered opening " << filename << std::endl;
        file.close();
        return;
    }
    file >> size;
    size = size*size;
    int value;
    while(file >> value) {
        entries.push_back(value);
    }
    file.close();
}

void Game::Print() {
    for(int i = 0; i < entries.size(); ++i) {
        if(i > 0 && i%size == 0) {
            std::cout << std::endl;
        }
        std::cout << entries.at(i) << " ";
    }
    std::cout << std::endl;
}

std::vector<int>
Game::EmptyEntries() {
    std::vector<int> ret;
    for(int i = 0; i < entries.size(); ++i) {
        if(entries.at(i) == 0) {
            ret.push_back(i);
        }
    }
    return ret;
}

std::vector<int>
Game::Intercept(std::vector<int> a, std::vector<int> b) {
    std::vector<int> elems;
    elems.insert(elems.end(), a.begin(), a.end());
    elems.insert(elems.end(), b.begin(), b.end());
    std::sort(elems.begin(), elems.end());
    std::vector<int>::iterator it = std::unique(elems.begin(), elems.end());
    std::vector<int> ret;
    ret.insert(ret.end(), it, elems.end());
    return ret;

}

std::vector<int>
Game::Intercept3(std::vector<int> a, std::vector<int> b, std::vector<int> c) {
    std::vector<int> ret;
    a.erase(std::remove_if(a.begin(), a.end(), [](int x){return x==0;}),a.end());
    b.erase(std::remove_if(b.begin(), b.end(), [](int x){return x==0;}),b.end());
    c.erase(std::remove_if(c.begin(), c.end(), [](int x){return x==0;}),c.end());
    ret = Intercept(a,b);
    ret = Intercept(ret,c);
    return ret;
}

void Game::Solve() {
    std::vector<int> empties = EmptyEntries();
    int sqrtsize = sqrt(size);
    for(const auto& entry : empties) {
        int x = entry%size;
        int y = entry/size;
        int block = (x/sqrtsize)*sqrtsize+y/sqrtsize;
        std::cout << GetColumn(x) << std::endl;
        std::cout << GetRow(y) << std::endl;
        std::cout << GetBlock(block) << std::endl;

    }
}
    


// i is 0-indexed.
std::vector<int> 
Game::GetColumn(int i) {
    std::vector<int> ret;
    int count = i;
    while(count < size*size) {
        ret.push_back(entries.at(count));
        count+=size;
    }
    return ret;
}

// i is 0-indexed.
std::vector<int>
Game::GetRow(int i) {
    std::vector<int> ret;
    int count = i*size;
    for(int count = i*size; count < (i+1)*size; ++count) {
        ret.push_back(entries.at(count));
    }
    return ret;
}

// i is 0-indexed.
std::vector<int>
Game::GetBlock(int i) {
    std::vector<int> ret;
    int sqrtsize = sqrt(size);
    int x = i/sqrtsize;
    int y = i%sqrtsize;
    std::vector<std::vector<int>> rows;
    for(int r = y*sqrtsize; r < (y+1)*sqrtsize; ++r) {
        rows.push_back(GetRow(r));
    }

    for(const auto& r : rows) {
        std::vector<int>::const_iterator first = r.begin() + x*sqrtsize;
        std::vector<int>::const_iterator last = r.begin() + (x+1)*sqrtsize;
        std::vector<int> newVec(first,last);
        ret.insert(ret.end(), newVec.begin(), newVec.end());
    }
    return ret;
}

