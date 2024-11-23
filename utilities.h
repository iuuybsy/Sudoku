#ifndef SUDOKU_UTILITIES_H
#define SUDOKU_UTILITIES_H

#include <vector>

using std::vector;

void print_table(const vector<vector<int>> &table);
void print_vector(const vector<int> &vec);

int random_valid_int(int min_val, int max_val);

bool is_valid(const vector<vector<int>> &sudoku, int row, int col, int num);
void dfs_generate(vector<vector<int>> &sudoku, vector<vector<bool>> &unvisited,
                  const vector<int> &numbers, int row, int col, int &settled_num);

#endif //SUDOKU_UTILITIES_H
