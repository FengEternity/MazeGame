#pragma once
#include <vector>

class Maze {
public:
    Maze(int rows, int cols);
    void generateMaze(int r, int c);
    void drawMaze();
    void saveMaze();
    void loadMaze();

    int getRows() const;   // ����
    int getCols() const;   // ����
    const std::vector<std::vector<int>>& getMaze() const; // ����

private:
    int rows, cols;
    std::vector<std::vector<int>> maze;
    void initMaze();
};
