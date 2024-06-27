#pragma once
#include "Maze.h"
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>  // ������ͷ�ļ�

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
    std::stack<std::pair<int, int>> path;  // ����DFS��ջ
    std::queue<std::pair<int, int>> explorationQueue;  // ����BFS�Ķ���
    std::unordered_map<int, std::pair<int, int>> cameFrom;  // ȷ�������� cameFrom
    void explore();
    bool pathFound;
};
