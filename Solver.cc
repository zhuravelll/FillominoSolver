    #include <chrono>
    #include <iostream>
    #include "Grid.h"
    bool Grid::check_indices(int r, int c) const {
        return r >= 0 && r < height && c >= 0 && c < width;
    }

    void Grid::update_vision(int idx, int signal) {
        for (int k = 0; k < vision_sz[idx]; ++k) {          //перевіряє всі 8 напрямків для 1
            vision_count[vision_adj[idx][k]] += signal;
        }
    }

    int Grid::get_size(int idx, int value, bool count_zeros) {
        current_stamp++; 
        vis_stamp[idx] = current_stamp;

        int stack_idx[128]; 
        int stack_sz = 0;
        stack_idx[stack_sz++] = idx;
        int res = 0;                    //знайдені клітинки групи

        while (stack_sz > 0) {
            int curr_idx = stack_idx[--stack_sz];
            res++;
            
            if (count_zeros && res >= value) return res;

            for (int k = 0; k < adj_sz[curr_idx]; ++k) {   //беребераємо сусідів поточнох клітинки
                int nidx = adj[curr_idx][k];               
                if (vis_stamp[nidx] != current_stamp) {
                    int nv = cells[nidx];                  //дивимось яке чилсо в сусідній клітинці
                    if (nv == value || (count_zeros && nv == 0)) {
                        vis_stamp[nidx] = current_stamp;
                        stack_idx[stack_sz++] = nidx;
                    }
                }
            }
            if (!count_zeros && res > value) return res;
        }
        return res;
    }

        int Grid::add_smart_neighbors(int idx, std::vector<int>& order, std::vector<bool>& visited) {
        struct NCell { int idx, filled; };
        NCell arr[4];
        int cnt = 0;

        for (int k = 0; k < adj_sz[idx]; ++k) {
            int nidx = adj[idx][k];
            if (visited[nidx] == 0) {
                int f = 0;
                for (int d = 0; d < adj_sz[nidx]; ++d) {
                    if (cells[adj[nidx][d]] != 0) f++;
                }
                arr[cnt++] = {nidx, f};
            }
        }

        if (cnt > 1) {
            for (int i = 0; i < cnt - 1; ++i) {
                for (int j = 0; j < cnt - i - 1; ++j) {
                    if (arr[j].filled < arr[j+1].filled) {
                        std::swap(arr[j], arr[j+1]);
                    }
                }
            }
        }

        for (int i = 0; i < cnt; ++i) {
            visited[arr[i].idx] = 1;
            order.push_back(arr[i].idx);
        }
        return cnt;
    }
    
    bool Grid::main_Solver(std::vector<int>& order, int pos, std::vector<bool>& visited) {
        if (pos == (int)order.size()) return true;

        int idx = order[pos]; 
        int fv = cells[idx];

        if (fv != 0) {
            if (get_size(idx, fv, true) < fv) return false;

            int added = add_smart_neighbors(idx, order, visited);
            bool result = main_Solver(order, pos + 1, visited);

            for (int i = 0; i < added; ++i) {
                visited[order.back()] = 0;
                order.pop_back();
            }
            return result;
        }

        int added = add_smart_neighbors(idx, order, visited);

        int priority_list[14]; 
        int p_size = 0;
        bool in_list[14] = {false};

        for (int k = 0; k < adj_sz[idx]; ++k) {
            int nv = cells[adj[idx][k]];
            if (nv != 0 && nv < 200 && !in_list[nv]) {
                priority_list[p_size++] = nv;
                in_list[nv] = true;
            }
        }

        for (int v = 1; v <= maxVal; ++v) {
            if (!in_list[v]) priority_list[p_size++] = v;
        }

        for (int i = 0; i < p_size; ++i) {
            int v = priority_list[i];

            
            if (v == 1 && vision_count[idx] != 0) continue; 

            cells[idx] = v; 
            if (v == 1) update_vision(idx, +1);

            bool valid = true;

            int sz = get_size(idx, v, false);
            if (sz > v) valid = false;
            else if (sz != v) {
                int pot = get_size(idx, v, true);
                if (pot < v) valid = false;
            }

            if (valid) {
                for (int k = 0; k < adj_sz[idx]; ++k) {
                    int nidx = adj[idx][k];
                    int nv = cells[nidx];
                    if (nv != 0 && nv != v) {
                        if (get_size(nidx, nv, true) < nv) {
                            valid = false; break;
                        }
                    }
                }
            }

            if (!valid) {
                if (v == 1) update_vision(idx, -1);
                cells[idx] = 0; 
                continue; 
            }

            if (main_Solver(order, pos + 1, visited)) return true;

            if (v == 1) update_vision(idx, -1);
            cells[idx] = 0;
        }

        for (int i = 0; i < added; ++i) {
            visited[order.back()] = 0;
            order.pop_back();
        }

        return false;
    }

   bool Grid::solve() {
    maxVal = std::max(width, height);
    for (int i = 0; i < height * width; ++i)
        if (cells[i] > maxVal) maxVal = cells[i];

    //Граф суміжності для запам'ятовування сусідів
    for (int i = 0; i < width * height; ++i) {
        int r = i / width, c = i % width;
        adj_sz[i] = 0;
        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = { 0, 0, -1, 1};
        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k], nc = c + dc[k];
            if (check_indices(nr, nc))
                adj[i][adj_sz[i]++] = nr * width + nc;
        }
    }

    //Лінія зору у 8 напрямках 
    for (int i = 0; i < width * height; ++i) {
        vision_sz[i] = 0; //кількість клітинок які бачить клітинка і у 8 напрямках
        int r = i / width, c = i % width;
        const int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
        const int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
        for (int d = 0; d < 8; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            while (check_indices(nr, nc)) {
                vision_adj[i][vision_sz[i]++] = nr * width + nc; 
                nr += dr[d]; nc += dc[d];
            }
        }
    }

    vision_count.assign(height * width, 0);
    for (int i = 0; i < height * width; ++i)
        if (cells[i] == 1) update_vision(i, +1);

    //Шукає та заповнює очевидні ходи,ще до початку основого алгоритму
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < height * width; ++i) {
            if (cells[i] != 0) continue;

            int only_v = -1, cnt = 0;
            for (int v = 1; v <= maxVal; ++v) {
                if (v == 1 && vision_count[i] != 0) continue;

                int sz = get_size(i, v, false);
                if (sz > v) continue;

                int pot = (sz == v) ? v : get_size(i, v, true);
                if (pot >= v) { only_v = v; cnt++; }
                if (cnt > 1) break;
            }

            if (cnt == 1) {
                cells[i] = only_v;
                if (only_v == 1) update_vision(i, +1);
                changed = true;
            }
        }
    }

    
    std::vector<bool> visited(height * width, 0);
    std::vector<int> order;
    order.reserve(height * width);

    int best_idx = 0, best_v = -1;
    for (int i = 0; i < height * width; ++i) {
        if (cells[i] > best_v) {
            best_v = cells[i];
            best_idx = i;
        }
    }

    visited[best_idx] = 1;
    order.push_back(best_idx);

    auto t0 = std::chrono::high_resolution_clock::now();
    bool result = main_Solver(order, 0, visited);
    auto t1 = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "\nTime: " << ms / 1000.0 << " с\n";

    return result;
}