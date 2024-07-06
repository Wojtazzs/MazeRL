#include "./qlearning.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

int QLearning::TakeAction(int state) {
    // std::cout << "s\n";
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    if (distribution(generator) < this->m_Epsilon) {
        // std::cout << "Rand from inner \n";
        std::uniform_int_distribution<int> distribution(0, 4 - 1);
        return distribution(generator);
    }
    // std::cout << "rand from outer\n";
    return std::distance(QMatrix[state], std::max_element(QMatrix[state], QMatrix[state] + MAZE_SIZE));
}

void QLearning::Train() {
    bool training = true;
    int count = 0;
    for (int epoch = 0; epoch <= this->m_Epochs; epoch++) {
        int position_x = this->m_maze.player[0];
        int position_y = this->m_maze.player[1];
        int state = this->PositionFromState(
                position_x,
                position_y);

        for (int i = 0; i <= this->repeat; i++) {
        // while (training && (count < this->repeat)) {
                int action = this->TakeAction(state);
                auto[new_position_x, new_position_y] = this->UpdatePosition(position_x, position_y, action);
                int new_state = this->PositionFromState(new_position_x, new_position_y);
                double reward = (new_position_x == position_x && new_position_y == position_y) ? 1.0 : -0.1;
                if (std::isnan(reward)) {
                    throw std::invalid_argument("reward can't be nan");
                }
                int action_of_choice = std::distance(QMatrix[state], std::max_element(QMatrix[state], QMatrix[state] + MAZE_SIZE));  // TODO(11jolek11): Implement
                double target = reward + this->m_Gamma * this->QMatrix[new_state][action_of_choice];
                if (std::isnan(target)) {
                    throw std::invalid_argument("target can't be nan");
                }
                double temp = this->m_Alpha * (target - QMatrix[state][action]);
                if (std::isnan(temp)) {
                    throw std::invalid_argument("temp can't be nan");
                }
                // QMatrix[state][action] += temp;
                if (!std::isnan(temp)) {
                    QMatrix[state][action] += temp;
                } else {
                    std::cout << "NaN\n";
                }
                state = new_state;
                position_x = new_position_x;
                position_y = new_position_y;

                if (position_x == this->m_maze.maze_end[0] || position_y == this->m_maze.maze_end[1]) {
                    std::cout << "\nEpoch: " + std::to_string(epoch) + " Rep: " + std::to_string(count) + "\n";
                    training = false;
                    break;
                }

                count++;
            }
        // }

        // this->m_maze.randomize_maze();
    }
}

