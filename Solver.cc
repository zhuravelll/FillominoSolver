#include "Solver.h"

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

bool Grid::check_indices(int i, int j) const {
    return i >= 0 && i < height && j >= 0 && j < width;
}

int Grid::get_size(int i, int j, int value, std::vector<bool>& visited, bool zero) {
    visited[i * width + j] = true; 
    int res = 1;

    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];

        if (check_indices(x, y)) {
            int idx = x * width + y;
            if (!visited[idx]) {
                int current_val = get(x, y); 
                if (current_val == value || (zero && current_val == 0)) {
                    res += get_size(x, y, value, visited, zero);
                }
            }
        }
    }
    return res;
}
//Метод перевіряє чи все поле заповнене правильно
bool Grid::isCorrect() {
    std::vector<bool> visited(height * width, false);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = i * width + j;

            if (!visited[idx]) {
                int val = get(i, j); 
                if (get_size(i, j, val, visited, false) != val)
                    return false;
            }
        }
    }
    return true;
}

bool Grid::solvePuzzle(int i, int j, std::vector<bool>& visited, int visited_count) {
    int idx = i * width + j;
    visited[idx]  = true;
    visited_count++;
    bool getsize_visited[10][10];
    int x,y;
    if(get(i, j) != 0 ){
        if(visited_count == height*width){
            if(isCorrect()){
                return true;
            }
            return false;
        }
    }

}