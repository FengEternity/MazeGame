#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include "Common.h"
#include <tchar.h>
#include <iostream>  // 用于调试输出

#define WIDTH  600  // 定义窗口宽度
#define HEIGHT 600  // 定义窗口高度
#define CELL_SIZE 20  // 定义迷宫单元格的大小

int main() {
    initgraph(WIDTH, HEIGHT);  // 初始化图形界面，设置窗口大小

    Difficulty difficulty = MEDIUM;  // 初始化难度为中等
    bool playerMode = true;  // 初始化为玩家模式
    bool playerSelected = false;  // 玩家模式是否已选择
    bool difficultySelected = false;  // 难度是否已选择

    UI ui(WIDTH, HEIGHT);  // 创建UI对象，传入窗口宽度和高度

    // 显示游戏开始界面并处理用户选择
    while (true) {
        cleardevice();  // 清除屏幕
        ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);  // 绘制开始界面
        FlushBatchDraw();  // 刷新显示

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测鼠标左键点击
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // 获取鼠标点击位置，转换为窗口坐标

            // 检查不同按钮的点击情况并更新状态
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 100, (WIDTH) / 2 + 60, 130)) {
                playerMode = true;  // 玩家玩
                playerSelected = true;
                std::cout << "Player mode selected: Player\n";  // 输出调试信息
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 150, (WIDTH) / 2 + 60, 180)) {
                playerMode = false;  // 电脑玩
                playerSelected = true;
                std::cout << "Player mode selected: Computer\n";  // 输出调试信息
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 300, (WIDTH) / 2 + 60, 330)) {
                difficulty = EASY;  // 简单难度
                difficultySelected = true;
                std::cout << "Difficulty selected: Easy\n";  // 输出调试信息
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 350, (WIDTH) / 2 + 60, 380)) {
                difficulty = MEDIUM;  // 中等难度
                difficultySelected = true;
                std::cout << "Difficulty selected: Medium\n";  // 输出调试信息
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 400, (WIDTH) / 2 + 60, 430)) {
                difficulty = HARD;  // 困难难度
                difficultySelected = true;
                std::cout << "Difficulty selected: Hard\n";  // 输出调试信息
            }
            if (playerSelected && difficultySelected &&
                ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 500, (WIDTH) / 2 + 60, 530)) {
                std::cout << "Starting game...\n";  // 输出调试信息
                break;  // 开始游戏，跳出循环
            }
        }
        Sleep(100);  // 避免CPU过度占用
    }

    bool playAgain = false;  // 是否重新开始游戏的标志
    do {
        std::cout << "Initializing maze and player...\n";  // 输出调试信息
        Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE, difficulty);  // 创建迷宫对象
        maze.generateMaze(1, 1);  // 生成迷宫
        std::cout << "Maze generated.\n";  // 输出调试信息

        std::cout << "Creating Player...\n";  // 输出调试信息
        Player player(maze, 1, 1);  // 创建玩家对象
        std::cout << "Player created.\n";  // 输出调试信息

        maze.drawMaze();  // 绘制迷宫
        std::cout << "Maze drawn.\n";  // 输出调试信息

        BeginBatchDraw();  // 开始双缓冲绘图
        while (true) {
            cleardevice();  // 清除屏幕
            maze.drawMaze();  // 绘制迷宫
            player.drawPlayer();  // 绘制玩家
            std::cout << "Drawing player at (" << player.getX() << ", " << player.getY() << ").\n";  // 输出玩家位置

            if (playerMode) {
                // 玩家模式下处理键盘输入
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
            }
            else {
                // 电脑模式下自动移动玩家
                player.autoMove();
                std::cout << "Player auto-moved to (" << player.getX() << ", " << player.getY() << ").\n";  // 输出调试信息
            }

            if (player.isAtEnd()) {
                // 玩家到达终点，显示胜利信息
                LPCTSTR message = _T("你赢了！");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
                EndBatchDraw();  // 结束双缓冲绘图
                std::cout << "Player reached the end.\n";  // 输出调试信息
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
    } while (playAgain);  // 根据用户选择判断是否重新开始游戏

    int c = _getch();  // 等待用户输入，防止程序立即退出
    closegraph();  // 关闭图形界面
    return 0;
}
