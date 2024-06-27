#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include "Common.h"
#include <tchar.h>
#include <iostream>  // ���ڵ������

#define CELL_SIZE 20  // �����Թ���Ԫ��Ĵ�С

int main() {
    Difficulty difficulty = MEDIUM;  // ��ʼ���Ѷ�Ϊ�е�
    bool playerMode = true;  // ��ʼ��Ϊ���ģʽ
    bool playerSelected = false;  // ���ģʽ�Ƿ���ѡ��
    bool difficultySelected = false;  // �Ѷ��Ƿ���ѡ��

    int rows = 30, cols = 30;  // Ĭ��������
    int width = cols * CELL_SIZE;  // ���ݵ�Ԫ���С���㴰�ڿ��
    int height = rows * CELL_SIZE;  // ���ݵ�Ԫ���С���㴰�ڸ߶�

    initgraph(width, height);  // ��ʼ��ͼ�ν��棬���ô��ڴ�С

    UI ui(width, height);  // ����UI���󣬴��봰�ڿ�Ⱥ͸߶�

    // ��ʾ��Ϸ��ʼ���沢�����û�ѡ��
    while (true) {
        cleardevice();  // �����Ļ
        ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);  // ���ƿ�ʼ����
        FlushBatchDraw();  // ˢ����ʾ

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // ������������
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // ��ȡ�����λ�ã�ת��Ϊ��������

            // ��鲻ͬ��ť�ĵ�����������״̬
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 100, (width) / 2 + 60, 130)) {
                playerMode = true;  // �����
                playerSelected = true;
                std::cout << "Player mode selected: Player\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 150, (width) / 2 + 60, 180)) {
                playerMode = false;  // ������
                playerSelected = true;
                std::cout << "Player mode selected: Computer\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 300, (width) / 2 + 60, 330)) {
                difficulty = EASY;  // ���Ѷ�
                rows = 25;
                cols = 25;
                difficultySelected = true;
                std::cout << "Difficulty selected: Easy\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 350, (width) / 2 + 60, 380)) {
                difficulty = MEDIUM;  // �е��Ѷ�
                rows = 40;
                cols = 40;
                difficultySelected = true;
                std::cout << "Difficulty selected: Medium\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 400, (width) / 2 + 60, 430)) {
                difficulty = HARD;  // �����Ѷ�
                rows = 40;
                cols = 70;
                difficultySelected = true;
                std::cout << "Difficulty selected: Hard\n";  // ���������Ϣ
            }
            if (playerSelected && difficultySelected &&
                ui.isButtonClicked(mousePos.x, mousePos.y, (width) / 2 - 60, 500, (width) / 2 + 60, 530)) {
                std::cout << "Starting game...\n";  // ���������Ϣ
                break;  // ��ʼ��Ϸ������ѭ��
            }
        }
        Sleep(100);  // ����CPU����ռ��
    }

    // ����ѡ����Ѷȵ������ڴ�С
    width = cols * CELL_SIZE;
    height = rows * CELL_SIZE;
    initgraph(width, height);  // ���³�ʼ��ͼ�ν��棬���ô��ڴ�С

    bool playAgain = false;  // �Ƿ����¿�ʼ��Ϸ�ı�־
    do {
        std::cout << "Initializing maze and player...\n";  // ���������Ϣ
        Maze maze(rows, cols, difficulty);  // �����Թ�����
        maze.generateMaze(1, 1);  // �����Թ�
        std::cout << "Maze generated.\n";  // ���������Ϣ

        std::cout << "Creating Player...\n";  // ���������Ϣ
        Player player(maze, 1, 1);  // ������Ҷ���
        std::cout << "Player created.\n";  // ���������Ϣ

        maze.drawMaze();  // �����Թ�
        std::cout << "Maze drawn.\n";  // ���������Ϣ

        BeginBatchDraw();  // ��ʼ˫�����ͼ
        while (true) {
            cleardevice();  // �����Ļ
            maze.drawMaze();  // �����Թ�
            player.drawPlayer();  // �������

            if (playerMode) {
                // ���ģʽ�´����������
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
                // ����ģʽ���Զ��ƶ����
                player.autoMove();
            }

            if (player.hasMoved()) {  // ��������ƶ�ʱ���������Ϣ
                std::cout << "Drawing player at (" << player.getX() << ", " << player.getY() << ").\n";
            }

            if (player.isAtEnd()) {
                // ��ҵ����յ㣬��ʾʤ����Ϣ
                LPCTSTR message = _T("��Ӯ�ˣ�");
                outtextxy(width / 2 - 30, height / 2, message);
                EndBatchDraw();  // ����˫�����ͼ
                std::cout << "Player reached the end.\n";  // ���������Ϣ
                break;
            }

            FlushBatchDraw();  // ˢ�»�����
            Sleep(50);  // ����ӳ��Ա������ռ��CPU
        }
        EndBatchDraw();  // ����˫�����ͼ

        // �ȴ��û�ѡ��������˳�
        while (true) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {  // ���س�������
                playAgain = true;
                break;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {  // ��ESC���˳�
                playAgain = false;
                break;
            }
            Sleep(100);  // ����CPU����ռ��
        }
    } while (playAgain);  // �����û�ѡ���ж��Ƿ����¿�ʼ��Ϸ

    int c = _getch();  // �ȴ��û����룬��ֹ���������˳�
    closegraph();  // �ر�ͼ�ν���
    return 0;
}
