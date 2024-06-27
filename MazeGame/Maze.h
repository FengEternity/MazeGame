#pragma once
#include <vector>
#include "Common.h"

class Maze {
public:
    Maze(int rows, int cols, Difficulty difficulty);  // 原来的构造函数
    Maze(Difficulty difficulty);  // 新的构造函数
    void generateMaze(int r, int c);
    void drawMaze();
    void saveMaze();
    void loadMaze();

    int getRows() const;
    int getCols() const;
    const std::vector<std::vector<int>>& getMaze() const;

private:
    int rows, cols;
    Difficulty difficulty;
    std::vector<std::vector<int>> maze;
    void initMaze();
    void carveMaze(int r, int c, int step);
};
