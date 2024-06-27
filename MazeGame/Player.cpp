#include "Player.h"
#include <graphics.h>

#define CELL_SIZE 20

Player::Player(Maze& maze, int startX, int startY) : maze(maze), x(startX), y(startY) {}

void Player::drawPlayer() {
    setfillcolor(RED);
    solidrectangle(y * CELL_SIZE, x * CELL_SIZE, (y + 1) * CELL_SIZE, (x + 1) * CELL_SIZE);
}

void Player::movePlayer(char direction) {
    const auto& mazeData = maze.getMaze();
    int rows = maze.getRows();
    int cols = maze.getCols();

    switch (direction) {
    case 'w':
        if (x > 0 && mazeData[x - 1][y] == 0) x--;
        break;
    case 's':
        if (x < rows - 1 && mazeData[x + 1][y] == 0) x++;
        break;
    case 'a':
        if (y > 0 && mazeData[x][y - 1] == 0) y--;
        break;
    case 'd':
        if (y < cols - 1 && mazeData[x][y + 1] == 0) y++;
        break;
    }
}

bool Player::isAtEnd() {
    return (x == maze.getRows() - 1 && y == maze.getCols() - 1);
}