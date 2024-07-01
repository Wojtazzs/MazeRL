
#include <iostream>
#include <stack>
#include <random>

#include "raylib/raylib.h"

const int WINDOW_SIZE = 800;
const int MAZE_SIZE = 20;
const int RECT_SIZE = (WINDOW_SIZE-10)/MAZE_SIZE;
const int RECT_WIDTH = 30;

using namespace std;

enum BlockType {
    Empty = 0,
    Wall = 1,
    Player = 2,
    Map_wall = 4,
    End = 5,
};

class Maze {
public:
    BlockType obj[MAZE_SIZE][MAZE_SIZE]{};
    int player[2]{};
    Maze() {
        this->randomize_maze();
    }
    void draw();
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void randomize_maze();
};

void Maze::draw() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (this->obj[x][y] == Wall or this->obj[x][y] == Map_wall){
                DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
            }
            else if (this->obj[x][y] == Player){
                //DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
                DrawCircle((RECT_SIZE*x)+30, (RECT_SIZE*y)+30, (float)RECT_WIDTH/3, RED);
            }
            else if (this->obj[x][y] == End) {
                DrawCircle((RECT_SIZE*x)+30, (RECT_SIZE*y)+30, (float)RECT_WIDTH/4, YELLOW);
            }
        }
    }
}

struct Position {
public:
    int x;
    int y;
};

enum Direction {
    Left = 0,
    Right = 1,
    Top = 2,
    Bottom = 3,
};

class DoneSides {
public:
    bool Left = false;
    bool Right = false;
    bool Top = false;
    bool Bottom = false;
    bool all() {
        if (this->Left and this->Right and this->Top and this->Bottom) {
            return true;
        }
        return false;
    }
    void clear() {
        this->Left = false;
        this->Right = false;
        this->Top = false;
        this->Bottom = false;
    }
};

bool has_adjecent(BlockType (*arr)[MAZE_SIZE][MAZE_SIZE], Position pos) {
    int number_of_adjecent = 0;
    if ((*arr)[pos.x][pos.y] == Map_wall) {
        return true;
    }
    if ((*arr)[pos.x-1][pos.y] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x+1][pos.y] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x][pos.y-1] == Empty) {
        number_of_adjecent += 1;
    }
    if ((*arr)[pos.x][pos.y+1] == Empty) {
        number_of_adjecent += 1;
    }
    if (number_of_adjecent > 1) {
        return true;
    }
    return false;
}

void Maze::randomize_maze() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> sides(0, 3);
    uniform_int_distribution<int> start(1, 18);

    int side = sides(gen);

    int end_x = 0, end_y = 0;

    if (side == Left) {
        end_x = 0;
        end_y = start(gen);
    } else if (side == Right) {
        end_x = 19;
        end_y = start(gen);
    } else if (side == Top) {
        end_x = start(gen);
        end_y = 19;
    } else if (side == Bottom) {
        end_x = start(gen);
        end_y = 0;
    } else {
        cout << "WTF!\n";
    }

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (x == 0 || y == 0 || x == 19 || y == 19) {
                this->obj[x][y] = Map_wall;
                continue;
            }
            this->obj[x][y] = Wall;
        }
    }
    this->obj[end_x][end_y] = End;

    Position pos{};
    stack<Position> position;
    position.push({.x=end_x, .y=end_y});

    DoneSides done;
    done.clear();

    while (!position.empty()) {
        pos = position.top();
        side = sides(gen);
        if (side == Left) {
            if (pos.x > 1 and !has_adjecent(&this->obj, {pos.x - 1, pos.y})) {
                this->obj[pos.x - 1][pos.y] = Empty;
                position.push({pos.x - 1, pos.y});
                done.clear();
            } else done.Left = true;

        } else if (side == Right) {
            if (pos.x < 18 and !has_adjecent(&this->obj, {pos.x + 1, pos.y})) {
                this->obj[pos.x + 1][pos.y] = Empty;
                position.push({pos.x + 1, pos.y});
                done.clear();
            } else done.Right = true;

        } else if (side == Top) {
            if (pos.y > 1 and !has_adjecent(&this->obj, {pos.x, pos.y-1})) {
                this->obj[pos.x][pos.y-1] = Empty;
                position.push({pos.x, pos.y-1});
                done.clear();
            } else done.Top = true;

        } else if (side == Bottom) {
            if (pos.y < 18 and !has_adjecent(&this->obj, {pos.x, pos.y + 1})) {
                this->obj[pos.x][pos.y + 1] = Empty;
                position.push({pos.x, pos.y + 1});
                done.clear();
            } else done.Bottom = true;
        }
        if (done.all()) {
            position.pop();
        }
    }

    // Spawn player randomly
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (x == 0 || y == 0 || x == 19 || y == 19) continue;
            if (this->obj[x][y] == Empty and !has_adjecent(&this->obj, {x, y})) {
                this->player[0] = x;
                this->player[1] = y;
                this->obj[player[0]][player[1]] = Player;
                return;
            }
        }
    }
}


void Maze::move_right() {
    if(this->obj[this->player[0]+1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] += 1;
        obj[this->player[0]][this->player[1]] = Player;
    }
    if(this->obj[this->player[0]+1][this->player[1]] == End) {
        cout << "WICTORY!\n";
        this->randomize_maze();
    }
}

void Maze::move_left() {
    if(this->obj[this->player[0]-1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] -= 1;
        obj[this->player[0]][this->player[1]] = Player;
    }
    if(this->obj[this->player[0]-1][this->player[1]] == End) {
        cout << "WICTORY!\n";
        this->randomize_maze();
    }
}

void Maze::move_down() {
    if(this->obj[this->player[0]][this->player[1]+1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] += 1;
        obj[this->player[0]][this->player[1]] = Player;
    }
    if(this->obj[this->player[0]][this->player[1]+1] == End) {
        cout << "WICTORY!\n";
        this->randomize_maze();
    }
}

void Maze::move_up() {
    if(this->obj[this->player[0]][this->player[1]-1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] -= 1;
        obj[this->player[0]][this->player[1]] = Player;
    }
    if(this->obj[this->player[0]][this->player[1]-1] == End) {
        cout << "WICTORY!\n";
        this->randomize_maze();
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    Maze maze;
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Maze");

    // TEMPORARY FOR USER INPUT
    SetTargetFPS(30);

    while (!WindowShouldClose()) {

        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            maze.move_right();
        }
        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            maze.move_left();
        }
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            maze.move_up();
        }
        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            maze.move_down();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        maze.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
