
#include <iostream>
#include <stack>
#include <string.h>
#include <experimental/random>

#include "external/glfw/src/internal.h"
#include "raylib/raylib.h"

const int WINDOW_SIZE = 800;
const int MAZE_SIZE = 20;
const int RECT_SIZE = (WINDOW_SIZE-10)/MAZE_SIZE;
const int RECT_WIDTH = 30;

using namespace std;

class Node {
    public:
        int x;
        int y;
};

enum BlockType {
    Empty = 0,
    Wall = 1,
    Player = 2,

    //FOR GENERATION
    Visited = 3,
    Map_wall = 4,
};

class Maze {
    public:
        BlockType obj[MAZE_SIZE][MAZE_SIZE];
        int player[2];
        Maze() {
            memset(player, 0, sizeof(player));
            player[0] = 2;
            player[1] = 2;

            memset(obj, 0, sizeof(obj));
            obj[1][1] = Wall;
            obj[player[0]][player[1]] = Player;

            // TO CHANGE FOR AUTO GENERATED MAZE------------------------------------------------------------------------
            obj[0][1] = Wall;
            obj[1][2] = Wall;
            obj[2][3] = Wall;
            obj[3][3] = Wall;
            obj[4][3] = Wall;
            for (int i = 0; i < MAZE_SIZE; i++) {
                obj[i][0] = Wall;
                obj[i][19] = Wall;
                obj[0][i] = Wall;
                obj[19][i] = Wall;
            }
            // ---------------------------------------------------------------------------------------------------------
        }
        void draw();
        void move_right();
        void move_left();
        void move_up();
        void move_down();
        void randomize_maze();
};

void Maze::draw() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (this->obj[x][y] == Wall){
                DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
            }
            else if (this->obj[x][y] == Player){
                //DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
                DrawCircle((RECT_SIZE*x)+30, (RECT_SIZE*y)+30, (float)RECT_WIDTH/3, RED);
            }
        }
    }
}

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

bool has_adjecent(BlockType (*arr)[MAZE_SIZE][MAZE_SIZE], Position pos) {
    int number_of_adjecent = 0;
    if ((*arr)[pos.x-1][pos.y] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x+1][pos.y] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x][pos.y-1] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x+1][pos.y+1] == Empty) {
        number_of_adjecent += 1;
    }
    if (number_of_adjecent > 1) {
        return true;
    }
    return false;
}

void Maze::randomize_maze() {
    int side = experimental::randint(0, 3);

    int end_x = 0, end_y = 0;

    if (side == Left) {
        end_x = 0;
        end_y = experimental::randint(0, MAZE_SIZE-1);
    } else if (side == Right) {
        end_x = 19;
        end_y = experimental::randint(0, MAZE_SIZE-1);
    } else if (side == Top) {
        end_x = experimental::randint(0, MAZE_SIZE-1);
        end_y = 19;
    } else if (side == Bottom) {
        end_x = experimental::randint(0, MAZE_SIZE-1);
        end_y = 0;
    } else {
        cout << "WTF!\n";
    }

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (x == 0 || y == 0 || x == 19 || y == 19) {
                this->obj[x][y] = Map_wall;
            }
            this->obj[x][y] = Wall;
        }
    }


    // Startujesz na end_x, end_y
    Position pos;
    stack<Position> position;
    position.push({.x=end_x, .y=end_y});
    while (!position.empty()) {
        pos = position.top();
        for (int dir = 0; dir < 4; dir++) {
            if (dir == Left) {
                if (!has_adjecent(&this->obj, {pos.x-1, pos.y})) {
                    position.push({pos.x-1, pos.y});
                    break;
                }
            }
        }
    }

}


void Maze::move_right() {
    if(this->obj[this->player[0]+1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] += 1;
        obj[this->player[0]][this->player[1]] = Player;

    }
}

void Maze::move_left() {
    if(this->obj[this->player[0]-1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] -= 1;
        obj[this->player[0]][this->player[1]] = Player;

    }
}

void Maze::move_down() {
    if(this->obj[this->player[0]][this->player[1]+1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] += 1;
        obj[this->player[0]][this->player[1]] = Player;

    }
}

void Maze::move_up() {
    if(this->obj[this->player[0]][this->player[1]-1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] -= 1;
        obj[this->player[0]][this->player[1]] = Player;

    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    constexpr int random_seed = 42;
    Maze maze;
    maze.randomize_maze();
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");

    // TEMPORARY FOR USER INPUT
    SetTargetFPS(240);

    while (!WindowShouldClose()) {

        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            maze.move_right();
        }
        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            maze.move_left();
        }
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            maze.move_up();
        }
        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            maze.move_down();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        maze.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
