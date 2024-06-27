#include "Player.h"
#include <graphics.h>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>  // ���ڵ������

#define CELL_SIZE 20  // ��Ԫ���С

Player::Player(Maze& maze, int startX, int startY) : maze(maze), x(startX), y(startY) {
    std::cout << "Initializing Player at (" << startX << ", " << startY << ")...\n";  // ���������Ϣ
    findPath();  // ��ʼ��ʱ�ҵ�·��
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

    switch (direction) {
    case 'w':
        if (x > 0 && mazeData[x - 1][y] == 0) x--;  // �����ƶ�
        break;
    case 's':
        if (x < rows - 1 && mazeData[x + 1][y] == 0) x++;  // �����ƶ�
        break;
    case 'a':
        if (y > 0 && mazeData[x][y - 1] == 0) y--;  // �����ƶ�
        break;
    case 'd':
        if (y < cols - 1 && mazeData[x][y + 1] == 0) y++;  // �����ƶ�
        break;
    }
}

bool Player::isAtEnd() {
    return (x == maze.getRows() - 3 && y == maze.getCols() - 3);  // �ж��Ƿ񵽴��յ�
}

void Player::findPath() {
    std::cout << "Finding path...\n";  // ���������Ϣ
    const auto& mazeData = maze.getMaze();  // ��ȡ�Թ�����
    int rows = maze.getRows();
    int cols = maze.getCols();
    std::queue<std::pair<int, int>> q;
    std::unordered_map<int, std::pair<int, int>> cameFrom;
    q.push({ x, y });
    cameFrom[x * cols + y] = { -1, -1 };

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // �����ĸ�����

    bool pathFound = false;  // ������������ʾ�Ƿ��ҵ�·��

    while (!q.empty()) {
        auto [cx, cy] = q.front();  // ��ǰ����
        q.pop();

        if (cx == rows - 1 && cy == cols - 1) {
            std::cout << "Reached the end of the maze at (" << cx << ", " << cy << ").\n";  // ���������Ϣ
            pathFound = true;  // �ҵ�·��
            break;  // �����յ�
        }

        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && mazeData[nx][ny] == 0) {
                if (cameFrom.find(nx * cols + ny) == cameFrom.end()) {
                    q.push({ nx, ny });
                    cameFrom[nx * cols + ny] = { cx, cy };  // ��¼·��
                    std::cout << "Moving to (" << nx << ", " << ny << ").\n";  // ���������Ϣ
                }
            }
        }
    }

    if (!pathFound) {
        std::cout << "No path found from start to end.\n";  // ���������Ϣ
        return;  // δ�ҵ�·����ֱ�ӷ���
    }

    int cx = rows - 1, cy = cols - 1;  // ���յ㿪ʼ����·��
    while (cx != -1 && cy != -1) {
        path.push_back({ cx, cy });
        std::tie(cx, cy) = cameFrom[cx * cols + cy];
        std::cout << "Path step: (" << cx << ", " << cy << ").\n";  // ���������Ϣ
    }

    std::reverse(path.begin(), path.end());  // ��ת·��
    std::cout << "Path found.\n";  // ���������Ϣ
}

void Player::autoMove() {
    if (!path.empty()) {
        x = path.front().first;  // �������λ��
        y = path.front().second;
        path.erase(path.begin());  // �Ƴ����߹���·��
    }
}

int Player::getX() const {
    return x;  // ������ҵ�X����
}

int Player::getY() const {
    return y;  // ������ҵ�Y����
}
