#include "Player.h"
#include <graphics.h>
#include <iostream>  // ���ڵ������
#include <thread>    // ��������ӳ�
#include <chrono>    // ��������ӳ�

#define CELL_SIZE 20  // ��Ԫ���С

Player::Player(Maze& maze, int startX, int startY) : maze(maze), x(startX), y(startY), moved(false), pathFound(false) {
    std::cout << "Initializing Player at (" << startX << ", " << startY << ")...\n";  // ���������Ϣ
    explorationQueue.push({ x, y });  // ��ʼ��ʱ�����������
    cameFrom[x * maze.getCols() + y] = { -1, -1 };
    std::cout << "Player initialized.\n";  // ���������Ϣ
}

void Player::drawPlayer() {
    setfillcolor(RED);  // ���������ɫΪ��ɫ
    solidrectangle(y * CELL_SIZE, x * CELL_SIZE, (y + 1) * CELL_SIZE, (x + 1) * CELL_SIZE);  // �������
}

void Player::movePlayer(char direction) {
    const auto& mazeData = maze.getMaze();  // ��ȡ�Թ�����
    int rows = maze.getRows();
    int cols = maze.getCols();

    moved = false; // �����ƶ�״̬

    switch (direction) {
    case 'w':
        if (x > 0 && mazeData[x - 1][y] == 0) {
            x--;  // �����ƶ�
            moved = true;
        }
        break;
    case 's':
        if (x < rows - 1 && mazeData[x + 1][y] == 0) {
            x++;  // �����ƶ�
            moved = true;
        }
        break;
    case 'a':
        if (y > 0 && mazeData[x][y - 1] == 0) {
            y--;  // �����ƶ�
            moved = true;
        }
        break;
    case 'd':
        if (y < cols - 1 && mazeData[x][y + 1] == 0) {
            y++;  // �����ƶ�
            moved = true;
        }
        break;
    }
}

bool Player::isAtEnd() {
    return (x == maze.getRows() - 3 && y == maze.getCols() - 3);  // �ж��Ƿ񵽴��յ�
}

void Player::explore() {
    const auto& mazeData = maze.getMaze();
    int rows = maze.getRows();
    int cols = maze.getCols();

    if (!explorationQueue.empty() && !pathFound) {
        auto [cx, cy] = explorationQueue.front();
        explorationQueue.pop();

        int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // �����ĸ�����

        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && mazeData[nx][ny] == 0) {
                if (cameFrom.find(nx * cols + ny) == cameFrom.end()) {
                    explorationQueue.push({ nx, ny });
                    cameFrom[nx * cols + ny] = { cx, cy };

                    // ����̽������
                    setfillcolor(BLUE);  // ������ɫΪ��ɫ
                    solidrectangle(ny * CELL_SIZE, nx * CELL_SIZE, (ny + 1) * CELL_SIZE, (nx + 1) * CELL_SIZE);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));  // �ӳ�50����

                    if (nx == rows - 3 && ny == cols - 3) {
                        pathFound = true;
                        break;
                    }
                }
            }
        }
    }

    if (pathFound) {
        path = std::stack<std::pair<int, int>>();  // ���ջ
        int cx = rows - 3, cy = cols - 3;
        while (cx != -1 && cy != -1) {
            path.push({ cx, cy });
            std::tie(cx, cy) = cameFrom[cx * cols + cy];
        }
    }
}

void Player::autoMove() {
    moved = false; // �����ƶ�״̬

    if (!pathFound) {
        explore();  // ���·��δ�ҵ�������̽��
    }
    else if (!path.empty()) {
        int newX = path.top().first;
        int newY = path.top().second;

        if (newX != x || newY != y) {
            x = newX;
            y = newY;
            moved = true;
        }

        path.pop();  // �Ƴ����߹���·��

        // ����ӳ��������ƶ��ٶ�
        std::this_thread::sleep_for(std::chrono::milliseconds(20));  // �ӳ�200����
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
