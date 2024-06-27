#pragma once
#include "Maze.h"
#include <vector>

class Player {
public:
    Player(Maze& maze, int startX, int startY);
    void drawPlayer();
    void movePlayer(char direction);
    void autoMove();
    bool isAtEnd();
    int getX() const;
    int getY() const;
    bool hasMoved() const; // 新增方法

private:
    Maze& maze;
    int x, y;
    std::vector<std::pair<int, int>> path;
    void findPath();
    bool moved; // 新增变量
};
