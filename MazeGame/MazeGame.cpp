#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include "Common.h"
#include <tchar.h>
#include <iostream>  // ���ڵ������

#define WIDTH  600  // ���崰�ڿ��
#define HEIGHT 600  // ���崰�ڸ߶�
#define CELL_SIZE 20  // �����Թ���Ԫ��Ĵ�С

int main() {
    initgraph(WIDTH, HEIGHT);  // ��ʼ��ͼ�ν��棬���ô��ڴ�С

    Difficulty difficulty = MEDIUM;  // ��ʼ���Ѷ�Ϊ�е�
    bool playerMode = true;  // ��ʼ��Ϊ���ģʽ
    bool playerSelected = false;  // ���ģʽ�Ƿ���ѡ��
    bool difficultySelected = false;  // �Ѷ��Ƿ���ѡ��

    UI ui(WIDTH, HEIGHT);  // ����UI���󣬴��봰�ڿ�Ⱥ͸߶�

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
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 100, (WIDTH) / 2 + 60, 130)) {
                playerMode = true;  // �����
                playerSelected = true;
                std::cout << "Player mode selected: Player\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 150, (WIDTH) / 2 + 60, 180)) {
                playerMode = false;  // ������
                playerSelected = true;
                std::cout << "Player mode selected: Computer\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 300, (WIDTH) / 2 + 60, 330)) {
                difficulty = EASY;  // ���Ѷ�
                difficultySelected = true;
                std::cout << "Difficulty selected: Easy\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 350, (WIDTH) / 2 + 60, 380)) {
                difficulty = MEDIUM;  // �е��Ѷ�
                difficultySelected = true;
                std::cout << "Difficulty selected: Medium\n";  // ���������Ϣ
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 400, (WIDTH) / 2 + 60, 430)) {
                difficulty = HARD;  // �����Ѷ�
                difficultySelected = true;
                std::cout << "Difficulty selected: Hard\n";  // ���������Ϣ
            }
            if (playerSelected && difficultySelected &&
                ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH) / 2 - 60, 500, (WIDTH) / 2 + 60, 530)) {
                std::cout << "Starting game...\n";  // ���������Ϣ
                break;  // ��ʼ��Ϸ������ѭ��
            }
        }
        Sleep(100);  // ����CPU����ռ��
    }

    bool playAgain = false;  // �Ƿ����¿�ʼ��Ϸ�ı�־
    do {
        std::cout << "Initializing maze and player...\n";  // ���������Ϣ
        Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE, difficulty);  // �����Թ�����
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
            std::cout << "Drawing player at (" << player.getX() << ", " << player.getY() << ").\n";  // ������λ��

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
                std::cout << "Player auto-moved to (" << player.getX() << ", " << player.getY() << ").\n";  // ���������Ϣ
            }

            if (player.isAtEnd()) {
                // ��ҵ����յ㣬��ʾʤ����Ϣ
                LPCTSTR message = _T("��Ӯ�ˣ�");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
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
