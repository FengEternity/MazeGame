#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include <tchar.h>  // 添加这个头文件

#define WIDTH  600  // 调整迷宫区域宽度
#define HEIGHT 600
#define CELL_SIZE 20

int main() {
    initgraph(WIDTH + 200, HEIGHT); // 增加UI区域

    Difficulty difficulty = MEDIUM;
    bool playerMode = true; // true 表示玩家玩，false 表示电脑玩
    bool playerSelected = false;
    bool difficultySelected = false;

    UI ui(WIDTH, HEIGHT);

    // 显示游戏开始界面
    while (true) {
        cleardevice();
        ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);
        FlushBatchDraw();

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 左键点击
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // 获取相对窗口的位置

            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 100, (WIDTH + 200) / 2 + 60, 130)) {
                playerMode = true; // 玩家玩
                playerSelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 150, (WIDTH + 200) / 2 + 60, 180)) {
                playerMode = false; // 电脑玩
                playerSelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 300, (WIDTH + 200) / 2 + 60, 330)) {
                difficulty = EASY; // 简单难度
                difficultySelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 350, (WIDTH + 200) / 2 + 60, 380)) {
                difficulty = MEDIUM; // 中等难度
                difficultySelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 400, (WIDTH + 200) / 2 + 60, 430)) {
                difficulty = HARD; // 困难难度
                difficultySelected = true;
            }
            if (playerSelected && difficultySelected &&
                ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 500, (WIDTH + 200) / 2 + 60, 530)) {
                // 开始游戏按钮被点击，且两个选项已选择
                break;
            }
        }
        Sleep(100);  // 避免CPU过度占用
    }

    bool playAgain = false;  // 新增变量
    do {
        // 初始化迷宫和玩家
        Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);
        maze.generateMaze(1, 1);

        Player player(maze, 1, 1);
        maze.drawMaze();

        BeginBatchDraw();  // 开始双缓冲绘图
        while (true) {
            cleardevice();
            maze.drawMaze();
            player.drawPlayer();

            // 使用GetAsyncKeyState处理键盘输入
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                player.movePlayer('w');
            }
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                player.movePlayer('s');
            }
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                player.movePlayer('a');
            }
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                player.movePlayer('d');
            }

            if (player.isAtEnd()) {
                LPCTSTR message = _T("你赢了！");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
                EndBatchDraw();  // 结束双缓冲绘图
                break;
            }

            FlushBatchDraw();  // 刷新缓冲区
            Sleep(50);  // 添加延迟以避免过度占用CPU
        }
        EndBatchDraw();  // 结束双缓冲绘图

        // 等待用户选择重玩或退出
        while (true) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {  // 按回车键重玩
                playAgain = true;
                break;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {  // 按ESC键退出
                playAgain = false;
                break;
            }
            Sleep(100);  // 避免CPU过度占用
        }
    } while (playAgain);

    int c = _getch();  // 处理返回值，但不使用
    closegraph();
    return 0;
}
