#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty) {
    setbkcolor(RGB(245, 245, 245));  // 设置背景颜色为浅灰色
    cleardevice();

    setbkmode(TRANSPARENT);  // 设置文字背景模式为透明
    settextcolor(BLACK);  // 设置文字颜色为黑色

    // 标题
    settextstyle(30, 0, _T("宋体"));
    outtextxy((width) / 2 - 60, 20, _T("选择模式"));

    // 绘制玩家选择框
    setfillcolor(playerSelected && playerMode ? RGB(0, 255, 0) : RGB(200, 200, 200));  // 玩家玩选择
    solidrectangle((width) / 2 - 60, 100, (width) / 2 + 60, 130);
    outtextxy((width) / 2 - 40, 105, _T("玩家玩"));

    setfillcolor(playerSelected && !playerMode ? RGB(0, 255, 0) : RGB(200, 200, 200));  // 电脑玩选择
    solidrectangle((width) / 2 - 60, 150, (width) / 2 + 60, 180);
    outtextxy((width) / 2 - 40, 155, _T("电脑玩"));

    // 绘制难度选择框
    outtextxy((width) / 2 - 60, 220, _T("选择难度"));
    setfillcolor(difficultySelected && difficulty == EASY ? RGB(0, 255, 0) : RGB(200, 200, 200));  // 简单难度选择
    solidrectangle((width) / 2 - 60, 300, (width) / 2 + 60, 330);
    outtextxy((width) / 2 - 20, 305, _T("简单"));

    setfillcolor(difficultySelected && difficulty == MEDIUM ? RGB(0, 255, 0) : RGB(200, 200, 200));  // 中等难度选择
    solidrectangle((width) / 2 - 60, 350, (width) / 2 + 60, 380);
    outtextxy((width) / 2 - 20, 355, _T("中等"));

    setfillcolor(difficultySelected && difficulty == HARD ? RGB(0, 255, 0) : RGB(200, 200, 200));  // 困难难度选择
    solidrectangle((width) / 2 - 60, 400, (width) / 2 + 60, 430);
    outtextxy((width) / 2 - 20, 405, _T("困难"));

    // 绘制开始游戏按钮
    setfillcolor(RGB(200, 200, 200));
    solidrectangle((width) / 2 - 60, 500, (width) / 2 + 60, 530);
    outtextxy((width) / 2 - 40, 505, _T("开始游戏"));

    // 添加提示信息
    settextstyle(20, 0, _T("宋体"));
    if (!playerSelected) {
        outtextxy((width) / 2 - 40, 570, _T("请选择模式"));
    }
    else if (!difficultySelected) {
        outtextxy((width) / 2 - 40, 570, _T("请选择难度"));
    }
}

bool UI::isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2) {
    return (mouseX > btnX1 && mouseX < btnX2 && mouseY > btnY1 && mouseY < btnY2);
}
