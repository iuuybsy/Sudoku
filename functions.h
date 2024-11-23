#ifndef SUDOKU_FUNCTIONS_H
#define SUDOKU_FUNCTIONS_H

#include <vector>

using std::vector;

void print_sudoku_table(const vector<vector<int>> &sudoku_table);

vector<vector<int>> generate_full_sudoku_table();
vector<vector<int>> generate_sudoku_problem();
void solve_sudoku(const vector<vector<int>> &sudoku_table);

#endif //SUDOKU_FUNCTIONS_H
