#pragma once
#include <vector>
#include "Common.h"  // 添加这一行

class Maze {
public:
    Maze(int rows, int cols, Difficulty difficulty);
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
    void carveMaze(int r, int c, int step);  // 新增
};
