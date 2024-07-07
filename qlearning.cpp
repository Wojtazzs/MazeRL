#include "./qlearning.hpp"

Actions Agent::get_action(State s) {
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

