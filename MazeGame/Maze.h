#pragma once
#include <vector>

class Maze {
public:
    Maze(int rows, int cols);
    void generateMaze(int r, int c);
    void drawMaze();
    void saveMaze();
    void loadMaze();

    int getRows() const;   // 新增
    int getCols() const;   // 新增
    const std::vector<std::vector<int>>& getMaze() const; // 新增

private:
    int rows, cols;
    std::vector<std::vector<int>> maze;
    void initMaze();
};
