#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty) {
    setbkcolor(RGB(245, 245, 245));  // ���ñ�����ɫΪǳ��ɫ
    cleardevice();

    setbkmode(TRANSPARENT);  // �������ֱ���ģʽΪ͸��
    settextcolor(BLACK);  // ����������ɫΪ��ɫ

    // ����
    settextstyle(30, 0, _T("����"));
    outtextxy((width) / 2 - 60, 20, _T("ѡ��ģʽ"));

    // �������ѡ���
    setfillcolor(playerSelected && playerMode ? RGB(0, 255, 0) : RGB(200, 200, 200));  // �����ѡ��
    solidrectangle((width) / 2 - 60, 100, (width) / 2 + 60, 130);
    outtextxy((width) / 2 - 40, 105, _T("�����"));

    setfillcolor(playerSelected && !playerMode ? RGB(0, 255, 0) : RGB(200, 200, 200));  // ������ѡ��
    solidrectangle((width) / 2 - 60, 150, (width) / 2 + 60, 180);
    outtextxy((width) / 2 - 40, 155, _T("������"));

    // �����Ѷ�ѡ���
    outtextxy((width) / 2 - 60, 220, _T("ѡ���Ѷ�"));
    setfillcolor(difficultySelected && difficulty == EASY ? RGB(0, 255, 0) : RGB(200, 200, 200));  // ���Ѷ�ѡ��
    solidrectangle((width) / 2 - 60, 300, (width) / 2 + 60, 330);
    outtextxy((width) / 2 - 20, 305, _T("��"));

    setfillcolor(difficultySelected && difficulty == MEDIUM ? RGB(0, 255, 0) : RGB(200, 200, 200));  // �е��Ѷ�ѡ��
    solidrectangle((width) / 2 - 60, 350, (width) / 2 + 60, 380);
    outtextxy((width) / 2 - 20, 355, _T("�е�"));

    setfillcolor(difficultySelected && difficulty == HARD ? RGB(0, 255, 0) : RGB(200, 200, 200));  // �����Ѷ�ѡ��
    solidrectangle((width) / 2 - 60, 400, (width) / 2 + 60, 430);
    outtextxy((width) / 2 - 20, 405, _T("����"));

    // ���ƿ�ʼ��Ϸ��ť
    setfillcolor(RGB(200, 200, 200));
    solidrectangle((width) / 2 - 60, 500, (width) / 2 + 60, 530);
    outtextxy((width) / 2 - 40, 505, _T("��ʼ��Ϸ"));

    // �����ʾ��Ϣ
    settextstyle(20, 0, _T("����"));
    if (!playerSelected) {
        outtextxy((width) / 2 - 40, 570, _T("��ѡ��ģʽ"));
    }
    else if (!difficultySelected) {
        outtextxy((width) / 2 - 40, 570, _T("��ѡ���Ѷ�"));
    }
}

bool UI::isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2) {
    return (mouseX > btnX1 && mouseX < btnX2 && mouseY > btnY1 && mouseY < btnY2);
}
