#include "./qlearning.hpp"
#include <climits>
#include <iostream>
#include <string>
#include <unistd.h>

State get_next_state(State s, Actions a) {
    State s_next = s;
    switch (a) {
        case UP:    s_next.x -= 1; break;
        case DOWN:  s_next.x += 1; break;
        case LEFT:  s_next.y -= 1; break;
        case RIGHT: s_next.y += 1; break;
    }
    return s_next;
}

void train_agent(Maze& maze, Agent& ql, int episodes) {
    srand((unsigned)time(0));
    for (int episode = 0; episode < episodes; ++episode) {
        State s = { maze.maze_start[0], maze.maze_start[1] };
        while (!maze.is_goal(s.x, s.y)) {
            Actions a = ql.get_action(s);
            State s_next = get_next_state(s, a);
            if (!maze.is_valid(s_next.x, s_next.y)) {
                s_next = s;  // if move not OK, stay
            }
            double reward = maze.is_goal(s_next.x, s_next.y) ? 100.0 : -1.0;
            ql.update(s, a, s_next, reward);
            s = s_next;
        }
    }
}

void test_agent(Maze& maze, Agent& ql) {
    State s = { maze.maze_start[0], maze.maze_start[1] };
    std::cout << "(" << s.x << ", " << s.y << ") -> ";
    State temp;
    while (!maze.is_goal(s.x, s.y)) {
        Actions a = ql.get_action(s);
        temp = get_next_state(s, a);
        if (maze.is_valid(temp.x, temp.y)) {
            s = temp;
        } else {
            continue;
        }
        std::cout << "(" << s.x << ", " << s.y << ") -> ";
        if (maze.is_goal(s.x, s.y)) {
            std::cout << "Goal Reached!" << std::endl;
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Maze maze;
    Agent solver;
    train_agent(maze, solver, 1000);
    State s = { maze.maze_start[0], maze.maze_start[1] };
    State temp;
    maze.pprint();

    std::cout << "START " + std::to_string(s.x) + "x" + std::to_string(s.y) + "\n";
    std::cout << "END   " + std::to_string(maze.maze_end[0]) + "x" + std::to_string(maze.maze_end[1]) + "\n";
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");

    sleep(2);
    // TEMPORARY FOR USER INPUT
    SetTargetFPS(30);
    std::cout << "(" << s.x << ", " << s.y << ") -> ";
    while (!WindowShouldClose()) {
        sleep(2);
        BeginDrawing();
        ClearBackground(BLACK);

        if (!maze.is_goal(s.x, s.y)) {
            Actions a = solver.get_action(s);
            temp = get_next_state(s, a);
            if (maze.is_valid(temp.x, temp.y)) {
                s = temp;
                maze.obj[s.x][s.y] = Player;
                // switch (a) {
                //     case UP:
                //         maze.move_up();
                //         break;
                //     case DOWN:
                //         maze.move_down();
                //         break;
                //     case LEFT:
                //         maze.move_left();
                //         break;
                //     case RIGHT:
                //         maze.move_right();
                //         break;
                // }
                std::cout << "(" << s.x << ", " << s.y << ") -> ";
                if (maze.is_goal(s.x, s.y)) {
                    std::cout << "Goal Reached!" << std::endl;
                }
            }
        }
        maze.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

