#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Game.hpp"


// Pretty printing of vectors.
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
	size = 3 * 3;

}

// Standard Sudoku game - currently the only option working.
Game::Game() {
    size = 3*3;
}

// Loads the game from a file.
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

// Prints the game to standard out.
void Game::Print() {
    for(unsigned i = 0; i < entries.size(); ++i) {
        if(i > 0 && i%size == 0) {
            std::cout << std::endl;
        }
        std::cout << entries.at(i) << " ";
    }
    std::cout << std::endl;
}

// Finds all entries which are 0 from a specified location.
std::vector<int>
Game::EmptyEntries(int from) {
    std::vector<int> ret;
    for(unsigned i = from; i < entries.size(); ++i) {
        if(entries.at(i) == 0) {
            ret.push_back(i);
        }
    }
    return ret;
}

// Finds the intersection betweem two vectors.
std::vector<int>
Game::Intersect(std::vector<int> a, std::vector<int> b) {
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	std::vector<int> ret;
	std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(ret));
    return ret;

}

// Inverse a list of elements in the set of [1-9]
std::vector<int>
Game::Inverse(std::vector<int> a) {
	std::vector<int> elems{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (const auto& e : a) {
		const auto iter = std::find(elems.begin(), elems.end(), e);
		if (iter != elems.end()) {
			elems.erase(iter);
		}
	}
	return elems;
}

// Finds the intersection between three vectors.
std::vector<int>
Game::Intersect3(std::vector<int> a, std::vector<int> b, std::vector<int> c) {
    std::vector<int> ret;
	// Remove zero from all entries
    a.erase(std::remove_if(a.begin(), a.end(), [](int x){return x==0;}),a.end());
    b.erase(std::remove_if(b.begin(), b.end(), [](int x){return x==0;}),b.end());
    c.erase(std::remove_if(c.begin(), c.end(), [](int x){return x==0;}),c.end());
    ret = Intersect(Inverse(a),Inverse(b));
    ret = Intersect(ret,Inverse(c));
    return ret;
}

// Check if the game has been completed.
bool Game::IsComplete() {
	for (const auto& e : entries) {
		if (e == 0) {
			return false;
		}
	}
	return true;
}

// Solving the game from a specified location.
// Call with 0 in order to solve the entire game.
void Game::Solve(int from) {

	// TODO: No need to recreate this list constantly. Create it and then just cut out from it.
    std::vector<int> empties = EmptyEntries(from);
    int sqrtsize = (int)sqrt(size);

	if (IsComplete()) {
		std::cout << "THIS IS A SOLUTION: " << std::endl;
		Print();
		std::cout << std::endl << std::endl;
	}

    for(const auto& entry : empties) {
        int x = entry%size;
        int y = entry/size;
        int block = (x/sqrtsize)*sqrtsize+y/sqrtsize;

		std::vector<int> possibilities = Intersect3(GetColumn(x), GetRow(y), GetBlock(block));

		if (possibilities.size() == 0) {
			entries.at(entry) = 0;
			return;
		}
		for (unsigned i = 0; i < possibilities.size(); ++i) {
			entries.at(entry) = possibilities.at(i);
			Solve(entry);
		}
		entries.at(entry) = 0;
		return;
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

// TODO: Are we doing redundant stuff here?

// i is 0-indexed.
std::vector<int>
Game::GetBlock(int i) {
    std::vector<int> ret;
    int sqrtsize = (int)sqrt(size);
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

