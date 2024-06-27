#pragma once
#include "Maze.h"

class Player {
public:
    Player(Maze& maze, int startX, int startY);
    void drawPlayer();
    void movePlayer(char direction);
    bool isAtEnd();

private:
    Maze& maze;
    int x, y;
};
