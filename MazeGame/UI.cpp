#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawUI() {
    setfillcolor(LIGHTGRAY);
    solidrectangle(width, 0, width + 200, height);

    // ���ư�ť
    setfillcolor(RGB(255, 165, 0));
    solidrectangle(width + 20, 50, width + 180, 100);
    outtextxy(width + 60, 65, _T("��ʼ��Ϸ"));

    solidrectangle(width + 20, 150, width + 180, 200);
    outtextxy(width + 60, 165, _T("������"));

    solidrectangle(width + 20, 250, width + 180, 300);
    outtextxy(width + 60, 265,_T( "�����"));

    solidrectangle(width + 20, 350, width + 180, 400);
    outtextxy(width + 60, 365, _T("�˳���Ϸ"));
}