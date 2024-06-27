#pragma once
#include "Maze.h"
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>  // 添加这个头文件

class Player {
public:
    Player(Maze& maze, int startX, int startY);
    void drawPlayer();
    void movePlayer(char direction);
    void autoMove();
    bool isAtEnd();
    int getX() const;
    int getY() const;
    bool hasMoved() const;

private:
    Maze& maze;
    int x, y;
    bool moved;
    std::stack<std::pair<int, int>> path;  // 用于DFS的栈
    std::queue<std::pair<int, int>> explorationQueue;  // 用于BFS的队列
    std::unordered_map<int, std::pair<int, int>> cameFrom;  // 确保声明了 cameFrom
    void explore();
    bool pathFound;
};
