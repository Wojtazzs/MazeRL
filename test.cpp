#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAZE_SIZE = 6;
const int ACTIONS = 4; // up, down, left, right

enum Actions { UP, DOWN, LEFT, RIGHT };

struct State {
    int x, y;
};

class Maze {
 public:
    int maze[MAZE_SIZE][MAZE_SIZE] = {
        { 0, 1, 0, 0, 0, 1},
        { 0, 1, 0, 1, 0, 1},
        { 0, 0, 0, 1, 0, 1},
        { 0, 1, 0, 1, 0, 1},
        { 0, 1, 5, 0, 0, 1},
        { 1, 1, 1, 1, 1, 1}
    };
    State start = {0, 0};
    State goal = {4, 2};

    bool is_goal(State s) {
        return s.x == goal.x && s.y == goal.y;
    }

    bool is_valid(State s) {
        if (s.x < 0 || s.x >= MAZE_SIZE || s.y < 0 || s.y >= MAZE_SIZE) {
            return false;
        }

        // return maze[s.x][s.y] == 0;
        return maze[s.x][s.y] != 1;
    }
};

class QLearning {
 public:
    double Q[MAZE_SIZE][MAZE_SIZE][ACTIONS];
    double alpha = 0.1;
    double gamma = 0.9;
    double epsilon = 0.1;

    QLearning() {
        // Init QMatrix
        for (int i = 0; i < MAZE_SIZE; ++i)
            for (int j = 0; j < MAZE_SIZE; ++j)
                for (int k = 0; k < ACTIONS; ++k)
                    Q[i][j][k] = 0.0;
    }

    Actions get_action(State s) {
        // if ((double)rand() / RAND_MAX < epsilon) {
        if (static_cast<double>(rand()) / RAND_MAX < epsilon) {
            return (Actions)(rand() % ACTIONS);
        } else {
            double max_value = -1e9;
            Actions best_action = UP;
            for (int a = 0; a < ACTIONS; ++a) {
                if (Q[s.x][s.y][a] > max_value) {
                    max_value = Q[s.x][s.y][a];
                    best_action = (Actions)a;
                }
            }
            return best_action;
        }
    }

    void update(State s, Actions a, State s_next, double reward) {
        double max_q_next = -1e9;
        for (int a_next = 0; a_next < ACTIONS; ++a_next) {
            if (Q[s_next.x][s_next.y][a_next] > max_q_next) {
                max_q_next = Q[s_next.x][s_next.y][a_next];
            }
        }
        Q[s.x][s.y][a] += alpha * (reward + gamma * max_q_next - Q[s.x][s.y][a]);
    }
};

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

void train_agent(Maze& maze, QLearning& ql, int episodes) {
    srand((unsigned)time(0));
    for (int episode = 0; episode < episodes; ++episode) {
        State s = maze.start;
        while (!maze.is_goal(s)) {
            Actions a = ql.get_action(s);
            State s_next = get_next_state(s, a);
            if (!maze.is_valid(s_next)) {
                s_next = s;  // if move not OK, stay in the same state
            }
            double reward = maze.is_goal(s_next) ? 100.0 : -1.0;
            ql.update(s, a, s_next, reward);
            s = s_next;
        }
    }
}

void test_agent(Maze& maze, QLearning& ql) {
    State s = maze.start;
    State temp;
    while (!maze.is_goal(s)) {
        Actions a = ql.get_action(s);
        temp = get_next_state(s, a);
        if (maze.is_valid(temp)) {
            s = temp;
        } else {
            continue;
        }
        std::cout << "(" << s.x << ", " << s.y << ") -> ";
        if (maze.is_goal(s)) {
            std::cout << "Goal Reached!" << std::endl;
        }
    }
}

int main() {
    Maze maze;
    QLearning ql;
    train_agent(maze, ql, 1000);
    test_agent(maze, ql);
    return 0;
}

