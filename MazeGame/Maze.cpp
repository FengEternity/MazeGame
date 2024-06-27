#include "Maze.h"
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#define CELL_SIZE 20

Maze::Maze(int rows, int cols) : rows(rows), cols(cols), maze(rows, std::vector<int>(cols, 1)) {
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
    maze[r][c] = 0; // 0 表示路

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    for (int i = 0; i < 4; i++) {
        int randIndex = rand() % 4;
        std::swap(directions[i], directions[randIndex]);
    }

    for (int i = 0; i < 4; i++) {
        int nr = r + directions[i][0] * 2;
        int nc = c + directions[i][1] * 2;

        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] == 1) {
            maze[r + directions[i][0]][c + directions[i][1]] = 0;
            generateMaze(nr, nc);
        }
    }
}

void Maze::drawMaze() {
    setfillcolor(RGB(255, 165, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                solidrectangle(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            }
        }
    }
    setfillcolor(WHITE);
    solidrectangle(0, 0, CELL_SIZE, CELL_SIZE); // 起点
    setfillcolor(GREEN);
    solidrectangle((cols - 1) * CELL_SIZE, (rows - 1) * CELL_SIZE, cols * CELL_SIZE, rows * CELL_SIZE); // 终点
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
