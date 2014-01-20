#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include <vector>
class Game {
    public:
        Game();
        Game(int gamesize);
        void Load(const std::string& filename);
        void Print();
        void Solve();
    private:
        std::vector<int> entries;
        int size;

};


#endif
