#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty) {
    setbkcolor(RGB(255, 255, 0));  // 设置背景颜色为黄色
    cleardevice();

    setbkmode(TRANSPARENT);  // 设置文字背景模式为透明
    settextcolor(BLACK);  // 设置文字颜色为黑色

    // 绘制玩家选择框
    setfillcolor(RGB(255, 165, 0));  // 修改选择框背景颜色为橙色
    solidrectangle((width + 200) / 2 - 80, 50, (width + 200) / 2 + 80, 200);
    outtextxy((width + 200) / 2 - 40, 60, _T("选择模式"));

    setfillcolor(playerSelected && playerMode ? RGB(0, 255, 0) : RGB(255, 165, 0));  // 玩家玩选择
    solidrectangle((width + 200) / 2 - 60, 100, (width + 200) / 2 + 60, 130);
    outtextxy((width + 200) / 2 - 40, 105, _T("玩家玩"));

    setfillcolor(playerSelected && !playerMode ? RGB(0, 255, 0) : RGB(255, 165, 0));  // 电脑玩选择
    solidrectangle((width + 200) / 2 - 60, 150, (width + 200) / 2 + 60, 180);
    outtextxy((width + 200) / 2 - 40, 155, _T("电脑玩"));

    // 绘制难度选择框
    solidrectangle((width + 200) / 2 - 80, 250, (width + 200) / 2 + 80, 400);
    outtextxy((width + 200) / 2 - 40, 260, _T("选择难度"));

    setfillcolor(difficultySelected && difficulty == EASY ? RGB(0, 255, 0) : RGB(255, 165, 0));  // 简单难度选择
    solidrectangle((width + 200) / 2 - 60, 300, (width + 200) / 2 + 60, 330);
    outtextxy((width + 200) / 2 - 20, 305, _T("简单"));

    setfillcolor(difficultySelected && difficulty == MEDIUM ? RGB(0, 255, 0) : RGB(255, 165, 0));  // 中等难度选择
    solidrectangle((width + 200) / 2 - 60, 350, (width + 200) / 2 + 60, 380);
    outtextxy((width + 200) / 2 - 20, 355, _T("中等"));

    setfillcolor(difficultySelected && difficulty == HARD ? RGB(0, 255, 0) : RGB(255, 165, 0));  // 困难难度选择
    solidrectangle((width + 200) / 2 - 60, 400, (width + 200) / 2 + 60, 430);
    outtextxy((width + 200) / 2 - 20, 405, _T("困难"));

    // 绘制开始游戏按钮
    setfillcolor(RGB(255, 165, 0));
    solidrectangle((width + 200) / 2 - 60, 500, (width + 200) / 2 + 60, 530);
    outtextxy((width + 200) / 2 - 40, 505, _T("开始游戏"));
}

bool UI::isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2) {
    return (mouseX > btnX1 && mouseX < btnX2 && mouseY > btnY1 && mouseY < btnY2);
}
