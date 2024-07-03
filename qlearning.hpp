#include "./maze.hpp"
#include <algorithm>
#include <cmath>
#include <tuple>

class QLearning {
 private:
    double m_Gamma, m_Alpha, m_Epsilon = 0;
    int m_Epochs = 1000;
    int m_number_of_actions = 4;
    int m_number_of_states = MAZE_SIZE*MAZE_SIZE;  // Need init. in constructor
    double m_lr = 0.1;
    const Maze& m_maze;  // Maze should outlive QLearning
    //            [number of statesx]  [number of actions]
    double QMatrix[MAZE_SIZE*MAZE_SIZE][4];

    static int PositionFromState(int x, int y) {
        return x*MAZE_SIZE + y;
    }
    std::tuple<int, int> UpdatePosition(int x, int y, int action) {
        std::tuple<int, int> new_position;
        switch (action) {
            case 0:
                new_position = std::make_tuple(x, std::max(0, y - 1));
                break;
            case 1:
                new_position = std::make_tuple(x, std::min(MAZE_SIZE - 1, y + 1));
                break;
            case 2:
                new_position = std::make_tuple(std::max(0, x - 1), y);
                break;
            case 3:
                new_position = std::make_tuple(std::min(MAZE_SIZE - 1, x + 1), y);
                break;
        }
        return (this->m_maze.obj[get<0>(new_position)][get<1>(new_position)] == 0) ? new_position : std::make_tuple(x, y);
    }

    int TakeAction(int state) {
        // TODO(11jolek11): Implement
        return 0;
    }

 public:
     QLearning(const Maze& maze, double lr, int no_of_epochs,
             double gamma, double alpha, double epsilon):
         m_maze(maze), m_lr(lr),
         m_Epochs(no_of_epochs),
         m_Gamma(gamma),
         m_Alpha(alpha),
         m_Epsilon(epsilon) {}

     void Train();  // TODO(11jolek11): Change return type?
     void Solve();  // TODO(11jolek11): Change return type?
     void Get();  // TODO(11jolek11): Change return type?
};
