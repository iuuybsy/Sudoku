#include "utilities.h"

const int N = 9;
const int DIRECTIONS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

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

bool is_sudoku_valid(const vector<vector<int>> &sudoku) {
    int count[9] = {0};
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (sudoku[i][j] == 0)
                return false;
            ++count[sudoku[i][j]];
            if (count[sudoku[i][j]] > N)
                return false;
            if (!is_valid(sudoku, i, j, sudoku[i][j]))
                return false;
        }
    }
    return true;
}

void dfs_solve(vector<vector<int>> &sudoku, const vector<vector<int>> &blank_index,
               vector<vector<int>> &solutions, std::map<int, int> &num_count,
               const vector<int> &numbers, int index, int &settled_num) {
    if (settled_num == N * N) {
        vector<int> cur_solution(blank_index.size(), 0);
        for (int i = 0; i != blank_index.size(); ++i) {
            cur_solution[i] = sudoku[blank_index[i][0]][blank_index[i][1]];
        }
        solutions.push_back(cur_solution);
        return;
    }
    if (index >= blank_index.size())
        return;
    for (int num : numbers) {
        if (num_count[num] == N)
            continue;
        if (is_valid(sudoku, blank_index[index][0], blank_index[index][1], num)) {
            sudoku[blank_index[index][0]][blank_index[index][1]] = num;
            ++num_count[num];
            ++settled_num;
            dfs_solve(sudoku, blank_index, solutions, num_count,
                      numbers, index + 1, settled_num);
            --settled_num;
            --num_count[sudoku[blank_index[index][0]][blank_index[index][1]]];
            sudoku[blank_index[index][0]][blank_index[index][1]] = 0;
        }
    }
}

int num_of_solutions(vector<vector<int>> &sudoku) {
    vector<vector<int>> blank_index;
    int settled_num = 0;
    std::map<int, int> num_count;

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j!= N; ++j) {
            if (sudoku[i][j] == 0) {
                blank_index.push_back({i, j});
            }
            else {
                ++settled_num;
                ++num_count[sudoku[i][j]];
            }
        }
    }

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<vector<int>> solutions;

    dfs_solve(sudoku, blank_index, solutions,
              num_count, numbers, 0, settled_num);

    for (auto cord : blank_index)
        sudoku[cord[0]][cord[1]] = 0;

    return solutions.size();
}



