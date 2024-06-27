#include "UI.h"
#include <graphics.h>

UI::UI(int width, int height) : width(width), height(height) {}

void UI::drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty) {
    setbkcolor(RGB(255, 255, 0));  // ���ñ�����ɫΪ��ɫ
    cleardevice();

    setbkmode(TRANSPARENT);  // �������ֱ���ģʽΪ͸��
    settextcolor(BLACK);  // ����������ɫΪ��ɫ

    // �������ѡ���
    setfillcolor(RGB(255, 165, 0));  // �޸�ѡ��򱳾���ɫΪ��ɫ
    solidrectangle((width + 200) / 2 - 80, 50, (width + 200) / 2 + 80, 200);
    outtextxy((width + 200) / 2 - 40, 60, _T("ѡ��ģʽ"));

    setfillcolor(playerSelected && playerMode ? RGB(0, 255, 0) : RGB(255, 165, 0));  // �����ѡ��
    solidrectangle((width + 200) / 2 - 60, 100, (width + 200) / 2 + 60, 130);
    outtextxy((width + 200) / 2 - 40, 105, _T("�����"));

    setfillcolor(playerSelected && !playerMode ? RGB(0, 255, 0) : RGB(255, 165, 0));  // ������ѡ��
    solidrectangle((width + 200) / 2 - 60, 150, (width + 200) / 2 + 60, 180);
    outtextxy((width + 200) / 2 - 40, 155, _T("������"));

    // �����Ѷ�ѡ���
    solidrectangle((width + 200) / 2 - 80, 250, (width + 200) / 2 + 80, 400);
    outtextxy((width + 200) / 2 - 40, 260, _T("ѡ���Ѷ�"));

    setfillcolor(difficultySelected && difficulty == EASY ? RGB(0, 255, 0) : RGB(255, 165, 0));  // ���Ѷ�ѡ��
    solidrectangle((width + 200) / 2 - 60, 300, (width + 200) / 2 + 60, 330);
    outtextxy((width + 200) / 2 - 20, 305, _T("��"));

    setfillcolor(difficultySelected && difficulty == MEDIUM ? RGB(0, 255, 0) : RGB(255, 165, 0));  // �е��Ѷ�ѡ��
    solidrectangle((width + 200) / 2 - 60, 350, (width + 200) / 2 + 60, 380);
    outtextxy((width + 200) / 2 - 20, 355, _T("�е�"));

    setfillcolor(difficultySelected && difficulty == HARD ? RGB(0, 255, 0) : RGB(255, 165, 0));  // �����Ѷ�ѡ��
    solidrectangle((width + 200) / 2 - 60, 400, (width + 200) / 2 + 60, 430);
    outtextxy((width + 200) / 2 - 20, 405, _T("����"));

    // ���ƿ�ʼ��Ϸ��ť
    setfillcolor(RGB(255, 165, 0));
    solidrectangle((width + 200) / 2 - 60, 500, (width + 200) / 2 + 60, 530);
    outtextxy((width + 200) / 2 - 40, 505, _T("��ʼ��Ϸ"));
}

bool UI::isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2) {
    return (mouseX > btnX1 && mouseX < btnX2 && mouseY > btnY1 && mouseY < btnY2);
}
