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
        void Solve(int from = 0);
        std::vector<int> GetColumn(int i);
        std::vector<int> GetRow(int i);
        std::vector<int> GetBlock(int i);
        std::vector<int> EmptyEntries(int from);
        std::vector<int> Intersect3(std::vector<int> a, std::vector<int> b, std::vector<int> c);
        std::vector<int> Intersect(std::vector<int> a, std::vector<int> b);
		bool IsComplete();
		std::vector<int> Inverse(std::vector<int> a);
    private:
        std::vector<int> entries;
        int size;

};


#endif
