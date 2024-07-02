#include "maze.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Maze maze;
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");

    // TEMPORARY FOR USER INPUT
    SetTargetFPS(30);

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
