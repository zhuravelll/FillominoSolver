#ifndef GRID_H
#define GRID_H
#include <vector>

class Grid {
public:
    std::vector<int> cells;
    int width, height;
    int maxVal;
    Grid(int w, int h);
    void set(int row, int col, int val);
    void show();
    bool check_indices(int r, int c) const;
    bool solve();

private:
    std::vector<int> vis_stamp;
    int current_stamp;

    std::vector<int> vision_count;
    void update_vision(int idx, int signal);

    int adj[121][4];
    int adj_sz[121];

    int vision_adj[121][50];
    int vision_sz[121];

    int add_smart_neighbors(int idx, std::vector<int>& order, std::vector<bool>& visited);
    bool main_Solver(std::vector<int>& order, int depth, std::vector<bool>& visited);
    int get_size(int idx, int value, bool count_zeros);
};

Grid initGrid(int type);

#endif