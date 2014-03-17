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
        std::vector<int> GetColumn(int i);
        std::vector<int> GetRow(int i);
        std::vector<int> GetBlock(int i);
        std::vector<int> EmptyEntries();
        std::vector<int> Intercept3(std::vector<int> a, std::vector<int> b, std::vector<int> c);
        std::vector<int> Intersect(std::vector<int> a, std::vector<int> b);
		std::vector<int> Inverse(std::vector<int> a);
    private:
        std::vector<int> entries;
        int size;

};


#endif
