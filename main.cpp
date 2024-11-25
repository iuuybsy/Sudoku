#include "functions.h"
#include "utilities.h"

#include <iostream>

const int N = 9;

int main() {
    auto test = generate_sudoku_problem(40);
    print_sudoku_table(test);
    solve_sudoku(test);
    return 0;
}
