#include "functions.h"

int main() {
    auto test = generate_full_sudoku_table();
    print_sudoku_table(test);
    return 0;
}
