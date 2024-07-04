#include "./qlearning.hpp"
#include <iostream>
#include <string>

int QLearning::TakeAction(int state) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    if (distribution(generator) < this->m_Epsilon) {

    }
    return std::distance(QMatrix[state], std::max_element(QMatrix[state], QMatrix[state] + MAZE_SIZE));
}

void QLearning::Train() {
    for (int epoch = 0; epoch <= this->m_Epochs; epoch++) {
        int position_x = this->m_maze.player[0];
        int position_y = this->m_maze.player[1];
        int state = this->PositionFromState(
                position_x,
                position_y);

        for (int i = 0; i <= this->repeat; i++) {
            int action = this->TakeAction(state);
            auto[new_position_x, new_position_y] = this->UpdatePosition(position_x, position_y, action);
            int new_state = this->PositionFromState(new_position_x, new_position_y);
            double reward = (new_position_x == position_x && new_position_y == position_y) ? 10 : -0.1;
            int action_of_choice = std::distance(QMatrix[state], std::max_element(QMatrix[state], QMatrix[state] + MAZE_SIZE));  // TODO(11jolek11): Implement
            double target = reward + this->m_Gamma * this->QMatrix[new_state][action_of_choice];
            QMatrix[state][action] =+ this->m_Alpha * (target - QMatrix[state][action]);
            state = new_state;
            position_x = new_position_x;
            position_y = new_position_y;

            if (position_x == this->m_maze.maze_end[0] || position_y == this->m_maze.maze_end[1]) {
                std::cout << "Epoch: " + std::to_string(epoch) + " Rep: " + std::to_string(i) + "\n";
                break;
            }
        }

        // this->m_maze.randomize_maze();
    }
}

