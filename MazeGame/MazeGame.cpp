#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include <tchar.h>  // 添加这个头文件

#define WIDTH  800
#define HEIGHT 600
#define CELL_SIZE 20

int main() {
    initgraph(WIDTH + 200, HEIGHT); // 增加UI区域

    Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);
    maze.generateMaze(1, 1);

    UI ui(WIDTH, HEIGHT);
    ui.drawUI();

    Player player(maze, 1, 1);
    maze.drawMaze();

    BeginBatchDraw();  // 开始双缓冲绘图
    while (true) {
        cleardevice();
        maze.drawMaze();
        ui.drawUI();
        player.drawPlayer();

        if (_kbhit()) {
            char input = _getch();
            player.movePlayer(input);
            if (player.isAtEnd()) {
                LPCTSTR message = _T("你赢了！");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
                EndBatchDraw();  // 结束双缓冲绘图
                break;
            }
        }

        FlushBatchDraw();  // 刷新缓冲区
    }
    EndBatchDraw();  // 结束双缓冲绘图

    _getch();
    closegraph();
    return 0;
}