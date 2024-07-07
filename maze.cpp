#include "./maze.hpp"

bool has_adjecent(BlockType (*arr)[MAZE_SIZE][MAZE_SIZE], Position pos) {
    int number_of_adjecent = 0;
    if ((*arr)[pos.x][pos.y] == Map_wall or (*arr)[pos.x][pos.y] == End) {
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

void Maze::draw() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (this->obj[x][y] == Wall or this->obj[x][y] == Map_wall){
                DrawRectangle(RECT_SIZE*x, RECT_SIZE*y, RECT_WIDTH, RECT_WIDTH, WHITE);
            } 
            else if (this->obj[x][y] == Player) {
                //DrawRectangle((RECT_SIZE*x)+15, (RECT_SIZE*y)+15, RECT_WIDTH, RECT_WIDTH, WHITE);
                DrawCircle((RECT_SIZE*x)+(RECT_SIZE/2), (RECT_SIZE*y)+(RECT_SIZE/2), (float)RECT_WIDTH/3, RED);
            }
            else if (this->obj[x][y] == End) {
                DrawCircle((RECT_SIZE*x)+(RECT_SIZE/2), (RECT_SIZE*y)+(RECT_SIZE/2), (float)RECT_WIDTH/4, YELLOW);
            }
        }
    }
}

void Maze::randomize_maze() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sides(0, 3);
    std::uniform_int_distribution<int> start(1, MAZE_SIZE-2);

    int side = sides(gen);

    int end_x = 0, end_y = 0;

    if (side == Left) {
        end_x = 0;
        end_y = start(gen);
    } else if (side == Right) {
        end_x = MAZE_SIZE-1;
        end_y = start(gen);
    } else if (side == Top) {
        end_x = start(gen);
        end_y = MAZE_SIZE-1;
    } else if (side == Bottom) {
        end_x = start(gen);
        end_y = 0;
    } else {
        std::cout << "WTF!\n";
    }

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (x == 0 || y == 0 || x == MAZE_SIZE-1 || y == MAZE_SIZE-1) {
                this->obj[x][y] = Map_wall;
                continue;
            }
            this->obj[x][y] = Wall;
        }
    }

    this->maze_end[0] = end_x;
    this->maze_end[1] = end_y;

    this->obj[end_x][end_y] = End;

    Position pos{};
    std::stack<Position> position;
    position.push({.x = end_x, .y = end_y});

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
            if (pos.x < MAZE_SIZE-1 and !has_adjecent(&this->obj, {pos.x + 1, pos.y})) {
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
            if (pos.y < MAZE_SIZE-1 and !has_adjecent(&this->obj, {pos.x, pos.y + 1})) {
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
            if (x == 0 || y == 0 || x == MAZE_SIZE-1 || y == MAZE_SIZE-1) continue;
            if (this->obj[x][y] == Empty and !has_adjecent(&this->obj, {x, y})) {
                this->player[0] = x;
                this->player[1] = y;
                this->maze_start[0] = x;
                this->maze_start[1] = y;
                this->obj[player[0]][player[1]] = Player;
                return;
            }
        }
    }
    abort();

    this->pprint();
}


void Maze::move_right() {
    if(this->obj[this->player[0]+1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] += 1;
        obj[this->player[0]][this->player[1]] = Player;
        std::cout << "R\n";
    }
    if(this->obj[this->player[0]+1][this->player[1]] == End) {
        std::cout << "VICTORY!\n";
        // this->randomize_maze();
    }
}

void Maze::move_left() {
    if(this->obj[this->player[0]-1][this->player[1]] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[0] -= 1;
        obj[this->player[0]][this->player[1]] = Player;
        std::cout << "L\n";
    }
    if(this->obj[this->player[0]-1][this->player[1]] == End) {
        std::cout << "VICTORY!\n";
        // this->randomize_maze();
    }
}

void Maze::move_down() {
    if(this->obj[this->player[0]][this->player[1]+1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] += 1;
        obj[this->player[0]][this->player[1]] = Player;
        std::cout << "D\n";
    }
    if(this->obj[this->player[0]][this->player[1]+1] == End) {
        std::cout << "VICTORY!\n";
        // this->randomize_maze();
    }
}

void Maze::move_up() {
    if(this->obj[this->player[0]][this->player[1]-1] == Empty) {
        obj[this->player[0]][this->player[1]] = Empty;
        player[1] -= 1;
        obj[this->player[0]][this->player[1]] = Player;
        std::cout << "U\n";
    }
    if(this->obj[this->player[0]][this->player[1]-1] == End) {
        std::cout << "VICTORY!\n";
        // this->randomize_maze();
    }
}

