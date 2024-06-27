#include "Player.h"
#include <graphics.h>
#include <iostream>  // 用于调试输出
#include <thread>    // 用于添加延迟
#include <chrono>    // 用于添加延迟

#define CELL_SIZE 20  // 单元格大小

Player::Player(Maze& maze, int startX, int startY) : maze(maze), x(startX), y(startY), moved(false), pathFound(false) {
    std::cout << "Initializing Player at (" << startX << ", " << startY << ")...\n";  // 输出调试信息
    explorationQueue.push({ x, y });  // 初始化时将起点加入队列
    cameFrom[x * maze.getCols() + y] = { -1, -1 };
    std::cout << "Player initialized.\n";  // 输出调试信息
}

void Player::drawPlayer() {
    setfillcolor(RED);  // 设置玩家颜色为红色
    solidrectangle(y * CELL_SIZE, x * CELL_SIZE, (y + 1) * CELL_SIZE, (x + 1) * CELL_SIZE);  // 绘制玩家
}

void Player::movePlayer(char direction) {
    const auto& mazeData = maze.getMaze();  // 获取迷宫数据
    int rows = maze.getRows();
    int cols = maze.getCols();

    moved = false; // 重置移动状态

    switch (direction) {
    case 'w':
        if (x > 0 && mazeData[x - 1][y] == 0) {
            x--;  // 向上移动
            moved = true;
        }
        break;
    case 's':
        if (x < rows - 1 && mazeData[x + 1][y] == 0) {
            x++;  // 向下移动
            moved = true;
        }
        break;
    case 'a':
        if (y > 0 && mazeData[x][y - 1] == 0) {
            y--;  // 向左移动
            moved = true;
        }
        break;
    case 'd':
        if (y < cols - 1 && mazeData[x][y + 1] == 0) {
            y++;  // 向右移动
            moved = true;
        }
        break;
    }
}

bool Player::isAtEnd() {
    return (x == maze.getRows() - 3 && y == maze.getCols() - 3);  // 判断是否到达终点
}

void Player::explore() {
    const auto& mazeData = maze.getMaze();
    int rows = maze.getRows();
    int cols = maze.getCols();

    if (!explorationQueue.empty() && !pathFound) {
        auto [cx, cy] = explorationQueue.front();
        explorationQueue.pop();

        int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // 定义四个方向

        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && mazeData[nx][ny] == 0) {
                if (cameFrom.find(nx * cols + ny) == cameFrom.end()) {
                    explorationQueue.push({ nx, ny });
                    cameFrom[nx * cols + ny] = { cx, cy };

                    // 绘制探索过程
                    setfillcolor(BLUE);  // 设置颜色为蓝色
                    solidrectangle(ny * CELL_SIZE, nx * CELL_SIZE, (ny + 1) * CELL_SIZE, (nx + 1) * CELL_SIZE);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // 延迟50毫秒

                    if (nx == rows - 3 && ny == cols - 3) {
                        pathFound = true;
                        break;
                    }
                }
            }
        }
    }

    if (pathFound) {
        path = std::stack<std::pair<int, int>>();  // 清空栈
        int cx = rows - 3, cy = cols - 3;
        while (cx != -1 && cy != -1) {
            path.push({ cx, cy });
            std::tie(cx, cy) = cameFrom[cx * cols + cy];
        }
    }
}

void Player::autoMove() {
    moved = false; // 重置移动状态

    if (!pathFound) {
        explore();  // 如果路径未找到，继续探索
    }
    else if (!path.empty()) {
        int newX = path.top().first;
        int newY = path.top().second;

        if (newX != x || newY != y) {
            x = newX;
            y = newY;
            moved = true;
        }

        path.pop();  // 移除已走过的路径

        // 添加延迟以限制移动速度
        std::this_thread::sleep_for(std::chrono::milliseconds(20));  // 延迟200毫秒
    }
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

bool Player::hasMoved() const {
    return moved;
}
