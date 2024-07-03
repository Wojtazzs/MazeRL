#include "./maze.hpp"
#include <cmath>

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
