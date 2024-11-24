#include "functions.h"

#include <iostream>

const int N = 9;

int main() {
    auto test = generate_full_sudoku_table();
    print_sudoku_table(test);
    std::cout << std::endl;
    for (int i = 3; i != 8; ++i)
        for (int j = 3; j!= 8; ++j)
            test[i][j] = 0;
    vector<vector<bool>> is_result(N, vector<bool>(N, false));
    solve_sudoku(test, is_result);
    return 0;
}
