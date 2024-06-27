#include "Maze.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
#include <random>

#define CELL_SIZE 20  // 单元格大小

Maze::Maze(int rows, int cols, Difficulty difficulty) : rows(rows), cols(cols), difficulty(difficulty), maze(rows, std::vector<int>(cols, 1)) {
    initMaze();
}

Maze::Maze(Difficulty difficulty) : difficulty(difficulty) {
    // 根据难度设置行数和列数
    switch (difficulty) {
    case EASY:
        rows = 20;
        cols = 20;
        break;
    case MEDIUM:
        rows = 30;
        cols = 30;
        break;
    case HARD:
        rows = 50;
        cols = 50;
        break;
    }
    maze = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 1));
    initMaze();
}

void Maze::initMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze[i][j] = 1; // 1 表示墙
        }
    }
}

void Maze::generateMaze(int r, int c) {
    std::srand(std::time(nullptr));
    carveMaze(r, c, 2);  // 使用步长2进行迷宫生成
    maze[0][0] = 0;  // 确保起点为可行路径
    maze[rows - 3][cols - 3] = 0;  // 确保终点为可行路径

    // 输出迷宫信息进行调试
    std::cout << "Generated maze:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Maze::carveMaze(int r, int c, int step) {
    std::stack<std::pair<int, int>> stack;
    stack.push({ r, c });
    maze[r][c] = 0;  // 设置起点为通路

    std::random_device rd;
    std::mt19937 g(rd());

    while (!stack.empty()) {
        auto [cr, cc] = stack.top();
        stack.pop();

        int directions[4][2] = { {-step, 0}, {step, 0}, {0, -step}, {0, step} };
        std::shuffle(std::begin(directions), std::end(directions), g);  // 使用 std::shuffle

        for (auto& dir : directions) {
            int nr = cr + dir[0];
            int nc = cc + dir[1];
            int midr = cr + dir[0] / 2;
            int midc = cc + dir[1] / 2;

            if (nr > 0 && nr < rows - 1 && nc > 0 && nc < cols - 1 && maze[nr][nc] == 1) {
                maze[nr][nc] = 0;  // 设置新的终点为通路
                maze[midr][midc] = 0;  // 设置中间点为通路
                stack.push({ nr, nc });
            }
        }
    }
}

void Maze::drawMaze() {
    setbkcolor(RGB(0, 0, 0));  // 设置背景颜色为黑色
    cleardevice();  // 清除屏幕
    setfillcolor(RGB(255, 165, 0));  // 设置填充颜色为橙色
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                solidrectangle(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            }
        }
    }
    setfillcolor(WHITE);
    solidrectangle(0, 0, CELL_SIZE, CELL_SIZE); // 起点
    solidrectangle((cols - 3) * CELL_SIZE, (rows - 3) * CELL_SIZE, (cols - 2) * CELL_SIZE, (rows - 2) * CELL_SIZE); // 终点
}

void Maze::saveMaze() {
    std::ofstream file("maze.txt");
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            file << cell << " ";
        }
        file << std::endl;
    }
    file.close();
}

void Maze::loadMaze() {
    std::ifstream file("maze.txt");
    for (auto& row : maze) {
        for (auto& cell : row) {
            file >> cell;
        }
    }
    file.close();
}

int Maze::getRows() const {
    return rows;
}

int Maze::getCols() const {
    return cols;
}

const std::vector<std::vector<int>>& Maze::getMaze() const {
    return maze;
}
