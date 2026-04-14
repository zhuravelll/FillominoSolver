#include <iostream>
#include <vector>
#include "Grid.h"
Grid::Grid(int w, int h) : width(w), height(h) {
    cells.resize(width * height, -1);
}
int Grid::get(int row, int col) const {
    return cells[row * width + col];
}
void Grid::set(int row, int col, int val) {
    cells[row * width + col] = val;
}
Grid initGrid() {
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