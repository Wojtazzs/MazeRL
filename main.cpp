
#include <iostream>
#include <string.h>
#include <experimental/random>

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

void Maze::randomize_maze() {
    int start_x = experimental::randint(0, MAZE_SIZE-1);
    int start_y = experimental::randint(0, MAZE_SIZE-1);

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            this->obj[x][y] = Wall;
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
