
#include "Grid.h"

Grid::Grid(int w, int h) : width(w), height(h), current_stamp(0) {
    cells.resize(w * h, 0);         //use 1d massiv for cache
    vis_stamp.resize(w * h, 0);     
}

void Grid::set(int row, int col, int val) {
    cells[row * width + col] = val;
}

Grid initGrid(int type) {
    if (type == 1) {
        Grid grid1(11, 11);
        grid1.set(0, 1, 2);
        grid1.set(0, 2, 6);
        grid1.set(0, 6, 2);
        grid1.set(0, 9, 2);

        grid1.set(1, 4, 13);
        grid1.set(1, 8, 3);
        grid1.set(1, 10, 2);

        grid1.set(2, 2, 8);
        grid1.set(2, 7, 5);
        grid1.set(2, 9, 3);

        grid1.set(3, 0, 8);
        grid1.set(3, 3, 1);
        grid1.set(3, 6, 2);
        grid1.set(3, 8, 5);

        grid1.set(4, 1, 6);
        grid1.set(4, 5, 2);
        grid1.set(4, 7, 2);
        grid1.set(4, 10, 4);

        grid1.set(5, 4, 3);
        grid1.set(5, 6, 4);

        grid1.set(6, 0, 2);
        grid1.set(6, 3, 3);
        grid1.set(6, 5, 4);
        grid1.set(6, 9, 4);

        grid1.set(7, 2, 2);
        grid1.set(7, 4, 3);
        grid1.set(7, 7, 4);
        grid1.set(7, 10, 2);

        grid1.set(8, 1, 4);
        grid1.set(8, 3, 2);
        grid1.set(8, 8, 3);

        grid1.set(9, 0, 3);
        grid1.set(9, 2, 4);
        grid1.set(9, 6, 2);

        grid1.set(10, 1, 3);
        grid1.set(10, 4, 2);
        grid1.set(10, 8, 1);
        grid1.set(10, 9, 7);
        return grid1;
    }
    else if (type == 2) {
        Grid grid2(6, 6);

        grid2.set(0, 1, 4);
        grid2.set(0, 3, 4);

        grid2.set(1, 2, 4);

        grid2.set(2, 0, 6);
        grid2.set(2, 2, 1);
        grid2.set(2, 3, 4);
        grid2.set(2, 5, 2);

        grid2.set(3, 0, 4);
        grid2.set(3, 2, 3);
        grid2.set(3, 3, 3);
        grid2.set(3, 5, 4);

        grid2.set(4, 3, 4);

        grid2.set(5, 2, 4);
        grid2.set(5, 4, 4);
        return grid2;
    }
    return Grid(1, 1);
}