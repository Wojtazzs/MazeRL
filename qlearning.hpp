#include "./maze.hpp"
#include <algorithm>
#include <cmath>
#include <tuple>
#include <random>

class QLearning {
 private:
    double m_Gamma, m_Alpha, m_Epsilon = 0;
    int m_Epochs = 1000;
    int m_number_of_actions = 4;
    int m_number_of_states = MAZE_SIZE*MAZE_SIZE;
    int repeat = 1;

    // std::random_device rand_dev;
    // std::mt19937 generator(rand_dev());
    // std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int TakeAction(int state);

 public:


    Maze& m_maze;  // Maze should outlive QLearning
    //            [number of states]  [number of actions]
    double QMatrix[MAZE_SIZE*MAZE_SIZE][4];
    static int PositionFromState(int x, int y) {
        return x*MAZE_SIZE + y;
    }

    std::tuple<int, int> UpdatePosition(int x, int y, int action) {
        std::tuple<int, int> new_position;
        switch (action) {
            case 0:
                new_position = std::make_tuple(x, std::max(0, y - 1));
                this->m_maze.move_left();
                break;
            case 1:
                new_position = std::make_tuple(x, std::min(MAZE_SIZE - 1, y + 1));
                this->m_maze.move_right();
                break;
            case 2:
                new_position = std::make_tuple(std::max(0, x - 1), y);
                this->m_maze.move_up();
                break;
            case 3:
                new_position = std::make_tuple(std::min(MAZE_SIZE - 1, x + 1), y);
                this->m_maze.move_down();
                break;
        }

        auto[return_x, return_y] = new_position;
        return (this->m_maze.obj[return_x][return_y] == 0) ? new_position : std::make_tuple(x, y);
    }

     QLearning(Maze& maze, int repeat, int no_of_epochs,
             double gamma, double alpha, double epsilon):
         m_maze(maze), repeat(repeat),
         m_Epochs(no_of_epochs),
         m_Gamma(gamma),
         m_Alpha(alpha),
         m_Epsilon(epsilon) {}

     void Train();  // TODO(11jolek11): Change return type?
     void Solve();  // TODO(11jolek11): Change return type?
};
