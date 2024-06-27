#pragma once
#include "Maze.h"
#include <vector>

class Player {
public:
    Player(Maze& maze, int startX, int startY);  // 构造函数，初始化玩家位置
    void drawPlayer();  // 绘制玩家
    void movePlayer(char direction);  // 移动玩家
    void autoMove(); // 自动移动方法
    bool isAtEnd();  // 判断是否到达终点
    int getX() const; // 获取玩家X位置
    int getY() const; // 获取玩家Y位置

private:
    Maze& maze;  // 迷宫引用
    int x, y;  // 玩家当前坐标
    std::vector<std::pair<int, int>> path; // 存储路径
    void findPath(); // 新增路径查找方法
};
