#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include <tchar.h>  // ������ͷ�ļ�

#define WIDTH  600  // �����Թ�������
#define HEIGHT 600
#define CELL_SIZE 20

int main() {
    initgraph(WIDTH + 200, HEIGHT); // ����UI����

    Difficulty difficulty = MEDIUM;
    bool playerMode = true; // true ��ʾ����棬false ��ʾ������
    bool playerSelected = false;
    bool difficultySelected = false;

    UI ui(WIDTH, HEIGHT);

    // ��ʾ��Ϸ��ʼ����
    while (true) {
        cleardevice();
        ui.drawStartUI(playerSelected, difficultySelected, playerMode, difficulty);
        FlushBatchDraw();

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // ������
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // ��ȡ��Դ��ڵ�λ��

            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 100, (WIDTH + 200) / 2 + 60, 130)) {
                playerMode = true; // �����
                playerSelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 150, (WIDTH + 200) / 2 + 60, 180)) {
                playerMode = false; // ������
                playerSelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 300, (WIDTH + 200) / 2 + 60, 330)) {
                difficulty = EASY; // ���Ѷ�
                difficultySelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 350, (WIDTH + 200) / 2 + 60, 380)) {
                difficulty = MEDIUM; // �е��Ѷ�
                difficultySelected = true;
            }
            if (ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 400, (WIDTH + 200) / 2 + 60, 430)) {
                difficulty = HARD; // �����Ѷ�
                difficultySelected = true;
            }
            if (playerSelected && difficultySelected &&
                ui.isButtonClicked(mousePos.x, mousePos.y, (WIDTH + 200) / 2 - 60, 500, (WIDTH + 200) / 2 + 60, 530)) {
                // ��ʼ��Ϸ��ť�������������ѡ����ѡ��
                break;
            }
        }
        Sleep(100);  // ����CPU����ռ��
    }

    bool playAgain = false;  // ��������
    do {
        // ��ʼ���Թ������
        Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);
        maze.generateMaze(1, 1);

        Player player(maze, 1, 1);
        maze.drawMaze();

        BeginBatchDraw();  // ��ʼ˫�����ͼ
        while (true) {
            cleardevice();
            maze.drawMaze();
            player.drawPlayer();

            // ʹ��GetAsyncKeyState�����������
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

            if (player.isAtEnd()) {
                LPCTSTR message = _T("��Ӯ�ˣ�");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
                EndBatchDraw();  // ����˫�����ͼ
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
    } while (playAgain);

    int c = _getch();  // ������ֵ������ʹ��
    closegraph();
    return 0;
}
