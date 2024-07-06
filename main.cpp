#include "./qlearning.hpp"
#include <climits>
#include <iostream>
#include <string>
#include <unistd.h>

// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     Maze maze;
//     InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");
//
//     // TEMPORARY FOR USER INPUT
//     SetTargetFPS(30);
//
//     while (!WindowShouldClose()) {
//
//         if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
//             maze.move_right();
//         }
//         if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
//             maze.move_left();
//         }
//         if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
//             maze.move_up();
//         }
//         if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
//             maze.move_down();
//         }
//
//         BeginDrawing();
//         ClearBackground(BLACK);
//         maze.draw();
//         EndDrawing();
//     }
//
//     CloseWindow();
//
//     return 0;
// }


int main() {
    std::cout << "Hello, World!" << std::endl;
    Maze maze;
    QLearning q(maze, 100, 100000, 0.9, 0.1, 0.2);
    q.Train();
    q.pprint();
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");
    sleep(3);
    // TEMPORARY FOR USER INPUT
    SetTargetFPS(30);

    int position_x = INT_MIN;
    int position_y = INT_MIN;
    int state = 0;

    // FIXME(11jolek11): Fix draw!
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        sleep(3);
        maze.draw();

        std::cout << "\nRefresh # New player position: [X:" + std::to_string(maze.player[0]) + " Y:" + std::to_string(maze.player[1]) + "] New state: ";
        state = q.PositionFromState(
                maze.player[0],
                maze.player[1]);
        std::cout << std::to_string(state);
        // int action =  std::distance(q.QMatrix[state], std::max_element(q.QMatrix[state], q.QMatrix[state] + MAZE_SIZE));
        int action = q.TakeAction(state);
        std::cout << " Action: " + std::to_string(action);

        std::cout << " Q: " + std::to_string(q.QMatrix[state][action]) + "\n";
        auto[position_x, position_y] = q.UpdatePosition(maze.player[0], maze.player[1], action);
        maze.obj[maze.player[0]][maze.player[1]] = Empty;
        maze.player[0] = position_x;
        maze.player[1] = position_y;
        maze.obj[maze.player[0]][maze.player[1]] = Player;
        // auto[maze.player[0], maze.player[1]] = q.UpdatePosition(position_x, position_y, action);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

