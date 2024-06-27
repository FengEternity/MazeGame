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
    bool hasMoved() const; // ��������

private:
    Maze& maze;
    int x, y;
    std::vector<std::pair<int, int>> path;
    void findPath();
    bool moved; // ��������
};
