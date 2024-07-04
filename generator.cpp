#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>

#define GENS 100000

class MazeGenerator {
 public:
    void fill();
    virtual void generate();
};

class OCAMazeGenerator: MazeGenerator {

};

const int row = 120;
const int column = 120;

int count_neigbours(const int board[][column], int r, int c) {
    int count = 0;
    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if ((i == r && j == c) || (i < 0 || j < 0) || (i >= row || j >= column)) {
                continue;
            }
            count += board[i][j];
        }
    }
    return count;
}

void pprint(const int board[][column]) {

    for (int i = 0; i < row; i++) {
        // std::cout << ":";
        for (int j = 0; j < column; j++) {
            // std::cout << "  " << b[i][j] << "  :";
            std::cout << board[i][j];
        }
        std::cout << "\n";
        // std::cout << "\n-----------------------------------------------------------\n";
    }
    std::cout << "----------------------------------\n"; 
}

int main() {
    int a[row][column], b[row][column] = {0};
    int neighbours_number = {0};
    srand(time(NULL));

    constexpr int row_margin = row / 3;
    constexpr int column_margin = column / 3;
    // std::cout << "Column margin: " + std::to_string(column_margin) << std::endl;

    for (int d = 0; d < 120; d++) {
        for (int i = row_margin; i < row - row_margin; i++) {
            for (int j = column_margin; j < column - column_margin; j++) {
                // std::cout << "Accessing: " + std::to_string(i) + "x" + std::to_string(j) + "\n";
                // int temp = rand() % 2;
                // std::cout << "GOT: " + std::to_string(temp) + " in " + std::to_string(i) + "x" + std::to_string(j) + "\n";
                a[i][j] = rand() % 2;
            }
        }
    }
    pprint(a);

    for (int d = 0; d < GENS; d++) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                neighbours_number = count_neigbours(a, i, j);
                if (a[i][j] == 1 && (neighbours_number >= 1 || neighbours_number <= 5)) {
                    b[i][j] = 1;
                } else if (a[i][j] == 0 && neighbours_number == 3) {
                    a[i][j] = 1;
                } else {
                    a[i][j] = 0;
                }
            }
        }
    }
    pprint(a);
}


