#include "functions.h"
#include "utilities.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <windows.h>
#include <map>

const int N = 9;

const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN;
const int WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int RED = FOREGROUND_RED;
const int COLORS[2][3] =
        {{YELLOW, WHITE, YELLOW}, {WHITE, YELLOW, WHITE}};

void print_sudoku_table(const vector<vector<int>> &sudoku_table) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (sudoku_table[i][j] == 0) {
                std::cout << "  ";
                continue;
            }
            SetConsoleTextAttribute(hConsole, COLORS[(i / 3) % 2][j / 3]);
            std::cout << sudoku_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

void print_sudoku_table(const vector<vector<int>> &sudoku_table,
                        const vector<vector<bool>> &sudoku_solution) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j) {
            if (sudoku_table[i][j] == 0) {
                std::cout << "  ";
                continue;
            }
            if (sudoku_solution[i][j])
                SetConsoleTextAttribute(hConsole, RED);
            else
                SetConsoleTextAttribute(hConsole, COLORS[(i / 3) % 2][j / 3]);
            std::cout << sudoku_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

vector<vector<int>> generate_full_sudoku_table() {
    vector<std::vector<int>> sudoku_table(N, vector<int>(N, 0));
    vector<std::vector<bool>> unvisited(N, vector<bool>(N, true));

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(numbers.begin(), numbers.end(), rng);

    int settled_num = 0;
    dfs_generate(sudoku_table, unvisited, numbers, 0, 0, settled_num);

    return sudoku_table;
}

vector<vector<int>> generate_sudoku_problem(int number_of_holes) {
    vector<vector<int>> sudoku_table = generate_full_sudoku_table();
    if (number_of_holes > N * N) {
        std::cout << "Number of holes is too large!" << std::endl;
        return sudoku_table;
    }

    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, N - 1);

    while (number_of_holes > 0) {
        int row = dis(gen);
        int col = dis(gen);
        while (sudoku_table[row][col] == 0) {
            row = dis(gen);
            col = dis(gen);
        }
        sudoku_table[row][col] = 0;
        --number_of_holes;
    }

    return sudoku_table;
}

void solve_sudoku(vector<vector<int>> &sudoku_table) {
    if (!is_sudoku_valid(sudoku_table)) {
        std::cout << "Sudoku table is invalid!" << std::endl;
        return;
    }

    vector<vector<int>> blank_index;
    int settled_num = 0;
    std::map<int, int> num_count;
    vector<vector<bool>> is_result(N, vector<bool>(N, false));

    for (int i = 0; i != N; ++i) {
        for (int j = 0; j!= N; ++j) {
            if (sudoku_table[i][j] == 0) {
                is_result[i][j] = true;
                blank_index.push_back({i, j});
            }
            else {
                ++settled_num;
                ++num_count[sudoku_table[i][j]];
                if (num_count[sudoku_table[i][j]] > N)
                    return;
            }
        }
    }

    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<vector<int>> solutions;

    dfs_solve(sudoku_table, blank_index, solutions,
              num_count, numbers, 0, settled_num);
    std::cout << "Number of solutions: " << solutions.size() << std::endl << std::endl;

    for (auto & solution : solutions) {
        for (int j = 0; j!= blank_index.size(); ++j) {
            sudoku_table[blank_index[j][0]][blank_index[j][1]] = solution[j];
        }
        print_sudoku_table(sudoku_table, is_result);
        std::cout << std::endl;
    }
}

