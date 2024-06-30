
#include <iostream>
#include <string.h>

#include "raylib/raylib.h"

const int WINDOW_SIZE = 800;
const int MAZE_SIZE = 20;
const int RECT_SIZE = (WINDOW_SIZE-10)/MAZE_SIZE;
const int RECT_WIDTH = 30;

class Node {
    public:
        int x;
        int y;
};

class Maze {
    public:
        int obj[MAZE_SIZE][MAZE_SIZE];
        int player[2];
        Maze() {
            memset(player, 0, sizeof(player));
            player[0] = 2;
            player[1] = 2;

            memset(obj, 0, sizeof(obj));
            obj[1][1] = 1;
            obj[player[0]][player[1]] = 2;

            // TO CHANGE FOR AUTO GENERATED MAZE------------------------------------------------------------------------
            obj[0][1] = 1;
            obj[1][2] = 1;
            obj[2][3] = 1;
            obj[3][3] = 1;
            obj[4][3] = 1;
            for (int i = 0; i < MAZE_SIZE; i++) {
                obj[i][0] = 1;
                obj[i][19] = 1;
                obj[0][i] = 1;
                obj[19][i] = 1;
            }
            // ---------------------------------------------------------------------------------------------------------
        }
        void draw();
        void move_right();
        void move_left();
        void move_up();
        void move_down();
};

void Maze::draw() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (this->obj[x][y] == 1){
                DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
            }
            else if (this->obj[x][y] == 2){
                //DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
                DrawCircle((RECT_SIZE*x)+30, (RECT_SIZE*y)+30, (float)RECT_WIDTH/3, RED);
            }
        }
    }
}

void Maze::move_right() {
    if(this->obj[this->player[0]+1][this->player[1]] == 0) {
        obj[this->player[0]][this->player[1]] = 0;
        player[0] += 1;
        obj[this->player[0]][this->player[1]] = 2;

    }
}

void Maze::move_left() {
    if(this->obj[this->player[0]-1][this->player[1]] == 0) {
        obj[this->player[0]][this->player[1]] = 0;
        player[0] -= 1;
        obj[this->player[0]][this->player[1]] = 2;

    }
}

void Maze::move_down() {
    if(this->obj[this->player[0]][this->player[1]+1] == 0) {
        obj[this->player[0]][this->player[1]] = 0;
        player[1] += 1;
        obj[this->player[0]][this->player[1]] = 2;

    }
}

void Maze::move_up() {
    if(this->obj[this->player[0]][this->player[1]-1] == 0) {
        obj[this->player[0]][this->player[1]] = 0;
        player[1] -= 1;
        obj[this->player[0]][this->player[1]] = 2;

    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    constexpr int random_seed = 42;
    Maze maze;

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
