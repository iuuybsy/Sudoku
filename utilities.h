#ifndef SUDOKU_UTILITIES_H
#define SUDOKU_UTILITIES_H

#include <vector>
#include <map>
#include <iostream>

using std::vector;

template<typename T>
void print_table(const vector<vector<T>> &table) {
    for (const auto & vec : table) {
        for (const auto &element : vec) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

bool is_valid(const vector<vector<int>> &sudoku, int row, int col, int num);
void dfs_generate(vector<vector<int>> &sudoku, vector<vector<bool>> &unvisited,
                  const vector<int> &numbers, int row, int col, int &settled_num);
bool is_sudoku_valid(const vector<vector<int>> &sudoku);
void dfs_solve(vector<vector<int>> &sudoku, const vector<vector<int>> &blank_index,
               vector<vector<int>> &solutions, std::map<int, int> &num_count,
               const vector<int> &numbers, int index, int &settled_num);
int num_of_solutions(vector<vector<int>> &sudoku);

#endif //SUDOKU_UTILITIES_H
