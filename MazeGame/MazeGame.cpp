#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include "Common.h"
#include <tchar.h>
#include <iostream>  // 用于调试输出
#include <thread>    // 用于添加延迟
#include <chrono>    // 用于添加延迟

#pragma comment(lib, "winmm.lib")  // 链接到winmm.lib

#define CELL_SIZE 20  // 定义迷宫单元格的大小

void playSound(const char* filename, bool loop = false) {
    char command[256];
    sprintf_s(command, "open %s alias %s", filename, filename);

    // 将 command 转换为宽字符字符串
    wchar_t wCommand[256];
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // 使用宽字符字符串调用 mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);

    sprintf_s(command, "play %s", filename);
    if (loop) {
        strcat_s(command, " repeat");
    }

    // 再次转换 command 为宽字符字符串
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // 使用宽字符字符串调用 mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);
}

void stopSound(const char* filename) {
    char command[256];
    sprintf_s(command, "close %s", filename);

    // 将 command 转换为宽字符字符串
    wchar_t wCommand[256];
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // 使用宽字符字符串调用 mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);
}

void showVictoryMessage(int width, int height);
void showOptions(int width, int height, bool& playAgain, bool& goToStart, bool& exitGame);

int main() {
    const int initialRows = 30, initialCols = 30;  // 初始行列数
    const int initialWidth = initialCols * CELL_SIZE;  // 初始窗口宽度
    const int initialHeight = initialRows * CELL_SIZE;  // 初始窗口高度

    Difficulty difficulty = MEDIUM;  // 初始化难度为中等
    bool playerMode = true;  // 初始化为玩家模式
    bool playerSelected = false;  // 玩家模式是否已选择
    bool difficultySelected = false;  // 难度是否已选择

    int rows = initialRows, cols = initialCols;  // 默认行列数
    int width = initialWidth;  // 窗口宽度
    int height = initialHeight;  // 窗口高度

    // 初始化图形界面，设置窗口大小
    initgraph(width, height);
    UI ui(width, height);  // 创建UI对象，传入窗口宽度和高度

    bool playAgain = false;  // 是否重新开始游戏的标志
    bool goToStart = true;  // 是否返回开始界面的标志
    bool exitGame = false;   // 是否退出游戏的标志

    // 播放背景音乐
    // playSound("background_music.mp3", true);

    // 主循环处理游戏逻辑
    while (true) {
        // 显示游戏开始界面并处理用户选择
        while (goToStart || (!playerSelected || !difficultySelected)) {
            cleardevice();  // 清除屏幕
            ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);  // 绘制开始界面
            FlushBatchDraw();  // 刷新显示

            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测鼠标左键点击
                POINT mousePos;
                GetCursorPos(&mousePos);
                ScreenToClient(GetHWnd(), &mousePos);  // 获取鼠标点击位置，转换为窗口坐标

                // 检查不同按钮的点击情况并更新状态
                if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 100, (width) / 2 + 60, 130)) {
                    playerMode = true;  // 玩家玩
                    playerSelected = true;
                    std::cout << "Player mode selected: Player\n";  // 输出调试信息
                }
                if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 150, (width) / 2 + 60, 180)) {
                    playerMode = false;  // 电脑玩
                    playerSelected = true;
                    std::cout << "Player mode selected: Computer\n";  // 输出调试信息
                }
                if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 300, (width) / 2 + 60, 330)) {
                    difficulty = EASY;  // 简单难度
                    rows = 25;
                    cols = 25;
                    difficultySelected = true;
                    std::cout << "Difficulty selected: Easy\n";  // 输出调试信息
                }
                if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 350, (width) / 2 + 60, 380)) {
                    difficulty = MEDIUM;  // 中等难度
                    rows = 40;
                    cols = 40;
                    difficultySelected = true;
                    std::cout << "Difficulty selected: Medium\n";  // 输出调试信息
                }
                if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 400, (width) / 2 + 60, 430)) {
                    difficulty = HARD;  // 困难难度
                    rows = 40;
                    cols = 70;
                    difficultySelected = true;
                    std::cout << "Difficulty selected: Hard\n";  // 输出调试信息
                }
                if (playerSelected && difficultySelected &&
                    ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 500, (width) / 2 + 60, 530)) {
                    std::cout << "Starting game...\n";  // 输出调试信息
                    goToStart = false;
                    // 播放游戏开始音效
                    playSound("start_game.mp3");
                    playSound("background_music.mp3", true);
                    break;  // 开始游戏，跳出循环
                }
            }
            Sleep(100);  // 避免CPU过度占用
        }

        // 根据选择的难度调整窗口大小
        width = cols * CELL_SIZE;
        height = rows * CELL_SIZE;
        initgraph(width, height);  // 重新初始化图形界面，设置窗口大小

        std::cout << "Initializing maze and player...\n";  // 输出调试信息
        Maze maze(rows, cols, difficulty);  // 创建迷宫对象
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

            if (playerMode) {
                // 玩家模式下处理键盘输入
                if (GetAsyncKeyState(VK_UP) & 0x8000) {
                    player.movePlayer('w');
                    playSound("move.wav");  // 播放移动音效
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    player.movePlayer('s');
                    playSound("move.wav");  // 播放移动音效
                }
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    player.movePlayer('a');
                    playSound("move.wav");  // 播放移动音效
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    player.movePlayer('d');
                    playSound("move.wav");  // 播放移动音效
                }
            }
            else {
                // 电脑模式下自动移动玩家
                player.autoMove();
                playSound("auto_move.wav");  // 播放自动移动音效
            }

            if (player.hasMoved()) {  // 仅在玩家移动时输出调试信息
                std::cout << "Drawing player at (" << player.getX() << ", " << player.getY() << ").\n";
            }

            if (player.isAtEnd()) {
                // 玩家到达终点，显示胜利信息
                stopSound("background_music.mp3");
                playSound("victory.mp3");  // 播放胜利音效
                showVictoryMessage(width, height);  // 显示“你赢了！”消息
                std::cout << "Player reached the end.\n";  // 输出调试信息
                break;
            }

            FlushBatchDraw();  // 刷新缓冲区
            Sleep(50);  // 添加延迟以避免过度占用CPU
        }
        EndBatchDraw();  // 结束双缓冲绘图

        // 等待用户选择重玩或退出
        showOptions(width, height, playAgain, goToStart, exitGame);

        if (exitGame) {
            break;  // 退出游戏
        }

        if (!playAgain && !goToStart) {
            break;  // 如果不重新开始，也不回到首页，则退出循环
        }

        // 关闭当前图形界面
        closegraph();

        if (goToStart) {
            // 重置窗口大小为初始状态
            width = initialWidth;
            height = initialHeight;
            rows = initialRows;
            cols = initialCols;
            initgraph(width, height);  // 重新初始化图形界面，设置窗口大小
            ui = UI(width, height);  // 重新创建UI对象
        }
        else {
            // 重新初始化图形界面，确保返回主界面时显示正常
            initgraph(width, height);
            ui = UI(width, height);  // 重新创建UI对象
        }
    }

    // 停止背景音乐
    // stopSound("background_music.mp3");

    closegraph();  // 关闭图形界面
    return 0;
}

void showVictoryMessage(int width, int height) {
    cleardevice();
    settextstyle(40, 0, _T("Arial"));  // 设置字体样式
    settextcolor(WHITE);
    outtextxy(width / 2 - 100, height / 2 - 20, _T("你赢了！"));
    FlushBatchDraw();
    std::this_thread::sleep_for(std::chrono::seconds(3));  // 显示3秒钟
}

void showOptions(int width, int height, bool& playAgain, bool& goToStart, bool& exitGame) {
    cleardevice();
    settextstyle(30, 0, _T("Arial"));
    settextcolor(WHITE);

    // 绘制按钮
    solidrectangle(width / 2 - 100, height / 2, width / 2 + 100, height / 2 + 30);
    solidrectangle(width / 2 - 100, height / 2 + 40, width / 2 + 100, height / 2 + 70);
    solidrectangle(width / 2 - 100, height / 2 + 80, width / 2 + 100, height / 2 + 110);

    // 绘制按钮文本
    outtextxy(width / 2 - 60, height / 2 + 5, _T("重新开始"));
    outtextxy(width / 2 - 60, height / 2 + 45, _T("回到首页"));
    outtextxy(width / 2 - 60, height / 2 + 85, _T("退出游戏"));
    FlushBatchDraw();

    while (true) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // 检测鼠标左键点击
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // 获取鼠标点击位置，转换为窗口坐标

            if (mousePos.x > width / 2 - 100 && mousePos.x < width / 2 + 100) {
                if (mousePos.y > height / 2 && mousePos.y < height / 2 + 30) {
                    playAgain = true;
                    goToStart = false;
                    exitGame = false;
                    break;
                }
                if (mousePos.y > height / 2 + 40 && mousePos.y < height / 2 + 70) {
                    playAgain = false;
                    goToStart = true;
                    exitGame = false;
                    break;
                }
                if (mousePos.y > height / 2 + 80 && mousePos.y < height / 2 + 110) {
                    playAgain = false;
                    goToStart = false;
                    exitGame = true;
                    break;
                }
            }
        }
        Sleep(100);  // 避免CPU过度占用
    }
}
