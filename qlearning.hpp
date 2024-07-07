#include "./maze.hpp"
#include <algorithm>
#include <iostream>
#include <tuple>
#include <random>

const int ACTIONS = 4;

enum Actions { UP, DOWN, LEFT, RIGHT };

struct State {
    int x, y;
};

class Agent {
 public:
    double Q[MAZE_SIZE][MAZE_SIZE][ACTIONS] = { 0.0 };
    double alpha = 0.1;
    double gamma = 0.9;
    double epsilon = 0.1;

    Agent(double alpha, double gamma, double epsilon):
        alpha(alpha), gamma(gamma), epsilon(epsilon) {}
    // Agent() {
        // Init QMatrix
        // for (int i = 0; i < MAZE_SIZE; ++i)
        //     for (int j = 0; j < MAZE_SIZE; ++j)
        //         for (int k = 0; k < ACTIONS; ++k)
        //             Q[i][j][k] = 0.0;
    // }

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

