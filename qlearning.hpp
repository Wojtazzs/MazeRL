#include "./maze.hpp"

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

    Actions get_action(State s);

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

