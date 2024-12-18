#ifndef SUDOKU_FUNCTIONS_H
#define SUDOKU_FUNCTIONS_H

#include <vector>

using std::vector;

void print_sudoku_table(const vector<vector<int>> &sudoku_table);
void print_sudoku_table(const vector<vector<int>> &sudoku_table,
                        const vector<vector<bool>> &sudoku_solution);

vector<vector<int>> generate_full_sudoku_table();
vector<vector<int>> generate_sudoku_problem(int number_of_holes);
void solve_sudoku(vector<vector<int>> &sudoku_table);

#endif //SUDOKU_FUNCTIONS_H
