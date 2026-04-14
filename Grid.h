#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
    std::vector<int> cells; // Плоский вектор для Cache Locality
    int width, height;
public:
    Grid(int w, int h);
    int get(int row, int col) const;
    void set(int row, int col, int val);
    void show();
    bool isCorrect();
    bool solvePuzzle(int i,int j,std::vector<bool>& visited,int visited_cout);
    int get_size(int i, int j, int value, std::vector<bool>& visited, bool zero);
    bool check_indices(int i, int j) const;
};
Grid initGrid();
#endif