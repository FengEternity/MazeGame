#include "Player.h"
#include <graphics.h>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>  // 用于调试输出

#define CELL_SIZE 20  // 单元格大小

Player::Player(Maze& maze, int startX, int startY) : maze(maze), x(startX), y(startY) {
    std::cout << "Initializing Player at (" << startX << ", " << startY << ")...\n";  // 输出调试信息
    findPath();  // 初始化时找到路径
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

    switch (direction) {
    case 'w':
        if (x > 0 && mazeData[x - 1][y] == 0) x--;  // 向上移动
        break;
    case 's':
        if (x < rows - 1 && mazeData[x + 1][y] == 0) x++;  // 向下移动
        break;
    case 'a':
        if (y > 0 && mazeData[x][y - 1] == 0) y--;  // 向左移动
        break;
    case 'd':
        if (y < cols - 1 && mazeData[x][y + 1] == 0) y++;  // 向右移动
        break;
    }
}

bool Player::isAtEnd() {
    return (x == maze.getRows() - 3 && y == maze.getCols() - 3);  // 判断是否到达终点
}

void Player::findPath() {
    std::cout << "Finding path...\n";  // 输出调试信息
    const auto& mazeData = maze.getMaze();  // 获取迷宫数据
    int rows = maze.getRows();
    int cols = maze.getCols();
    std::queue<std::pair<int, int>> q;
    std::unordered_map<int, std::pair<int, int>> cameFrom;
    q.push({ x, y });
    cameFrom[x * cols + y] = { -1, -1 };

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // 定义四个方向

    bool pathFound = false;  // 新增变量，表示是否找到路径

    while (!q.empty()) {
        auto [cx, cy] = q.front();  // 当前坐标
        q.pop();

        if (cx == rows - 1 && cy == cols - 1) {
            std::cout << "Reached the end of the maze at (" << cx << ", " << cy << ").\n";  // 输出调试信息
            pathFound = true;  // 找到路径
            break;  // 到达终点
        }

        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && mazeData[nx][ny] == 0) {
                if (cameFrom.find(nx * cols + ny) == cameFrom.end()) {
                    q.push({ nx, ny });
                    cameFrom[nx * cols + ny] = { cx, cy };  // 记录路径
                    std::cout << "Moving to (" << nx << ", " << ny << ").\n";  // 输出调试信息
                }
            }
        }
    }

    if (!pathFound) {
        std::cout << "No path found from start to end.\n";  // 输出调试信息
        return;  // 未找到路径，直接返回
    }

    int cx = rows - 1, cy = cols - 1;  // 从终点开始回溯路径
    while (cx != -1 && cy != -1) {
        path.push_back({ cx, cy });
        std::tie(cx, cy) = cameFrom[cx * cols + cy];
        std::cout << "Path step: (" << cx << ", " << cy << ").\n";  // 输出调试信息
    }

    std::reverse(path.begin(), path.end());  // 反转路径
    std::cout << "Path found.\n";  // 输出调试信息
}

void Player::autoMove() {
    if (!path.empty()) {
        x = path.front().first;  // 更新玩家位置
        y = path.front().second;
        path.erase(path.begin());  // 移除已走过的路径
    }
}

int Player::getX() const {
    return x;  // 返回玩家的X坐标
}

int Player::getY() const {
    return y;  // 返回玩家的Y坐标
}
