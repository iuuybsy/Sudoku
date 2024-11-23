#include "utilities.h"

#include <iostream>
#include <random>
#include <chrono>

const int N = 9;
const int DIRECTIONS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void print_table(const vector<vector<int>> &table) {
    for (const auto & vec : table) {
        for (int element : vec) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

void print_vector(const vector<int> &vec) {
    for (int element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int random_valid_int(int min_val, int max_val) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dist(min_val, max_val);
    int random_num = dist(rng);
    return random_num;
}

bool is_valid(const vector<vector<int>> &sudoku, int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (sudoku[row][i] == num || sudoku[i][col] == num)
            return false;
    }
    int block_row = row / 3;
    int block_col = col / 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (sudoku[block_row * 3 + i][block_col * 3 + j] == num)
                return false;
        }
    }
    return true;
}

void dfs_generate(vector<vector<int>> &sudoku, vector<vector<bool>> &unvisited,
                  const vector<int> &numbers, int row, int col, int &settles_num) {
    if (settles_num == N * N)
        return;
    if (row >= sudoku.size() || row < 0 || col >= sudoku[0].size() || col < 0)
        return;
    if (!unvisited[row][col])
        return;
    for (const int &num : numbers) {
        if (is_valid(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            unvisited[row][col] = false;
            ++settles_num;
            break;
        }
    }
    if (sudoku[row][col]== 0)
        return;
    for (auto direction : DIRECTIONS) {
        int next_row = row + direction[0];
        int next_col = col + direction[1];
        dfs_generate(sudoku, unvisited, numbers, next_row, next_col, settles_num);
    }
    if (settles_num < N * N) {
        sudoku[row][col] = 0;
        unvisited[row][col] = true;
        --settles_num;
    }
}
