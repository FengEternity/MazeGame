#pragma once
#include "Maze.h"
#include <vector>

class Player {
public:
    Player(Maze& maze, int startX, int startY);  // ���캯������ʼ�����λ��
    void drawPlayer();  // �������
    void movePlayer(char direction);  // �ƶ����
    void autoMove(); // �Զ��ƶ�����
    bool isAtEnd();  // �ж��Ƿ񵽴��յ�
    int getX() const; // ��ȡ���Xλ��
    int getY() const; // ��ȡ���Yλ��

private:
    Maze& maze;  // �Թ�����
    int x, y;  // ��ҵ�ǰ����
    std::vector<std::pair<int, int>> path; // �洢·��
    void findPath(); // ����·�����ҷ���
};
