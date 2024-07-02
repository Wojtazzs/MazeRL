#include <iostream>
#include <stack>
#include <random>

#include "raylib/raylib.h"

const int WINDOW_SIZE = 900;
const int MAZE_SIZE = 20;
const int RECT_SIZE = WINDOW_SIZE/MAZE_SIZE;
const int RECT_WIDTH = RECT_SIZE;

enum BlockType {
    Empty = 0,
    Wall = 1,
    Player = 2,
    Map_wall = 4,
    End = 5,
};


struct Position {
 public:
    int x;
    int y;
};

enum Direction {
    Left = 0,
    Right = 1,
    Top = 2,
    Bottom = 3,
};

class DoneSides {
 public:
    bool Left = false;
    bool Right = false;
    bool Top = false;
    bool Bottom = false;
    bool all() {
        if (this->Left and this->Right and this->Top and this->Bottom) {
            return true;
        }
        return false;
    }
    void clear() {
        this->Left = false;
        this->Right = false;
        this->Top = false;
        this->Bottom = false;
    }
};

class Maze {
 public:
    BlockType obj[MAZE_SIZE][MAZE_SIZE]{};
    int player[2]{};
    Maze() {
        this->randomize_maze();
    }
    void draw();
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void randomize_maze();
};

