#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawUI() {
    setfillcolor(LIGHTGRAY);
    solidrectangle(width, 0, width + 200, height);

    // 绘制按钮
    setfillcolor(RGB(255, 165, 0));
    solidrectangle(width + 20, 50, width + 180, 100);
    outtextxy(width + 60, 65, _T("开始游戏"));

    solidrectangle(width + 20, 150, width + 180, 200);
    outtextxy(width + 60, 165, _T("电脑玩"));

    solidrectangle(width + 20, 250, width + 180, 300);
    outtextxy(width + 60, 265,_T( "玩家玩"));

    solidrectangle(width + 20, 350, width + 180, 400);
    outtextxy(width + 60, 365, _T("退出游戏"));
}