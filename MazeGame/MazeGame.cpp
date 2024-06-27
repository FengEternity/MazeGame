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

    UI ui(WIDTH, HEIGHT);

    bool playAgain = false;  // ��������
    do {
        // ��ʼ���Թ������
        Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);
        maze.generateMaze(1, 1);

        Player player(maze, 1, 1);
        maze.drawMaze();

        // �ȴ��û������ʼ��Ϸ��ť
        while (true) {
            cleardevice();
            maze.drawMaze();
            ui.drawUI();
            FlushBatchDraw();

            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // ������
                POINT mousePos;
                GetCursorPos(&mousePos);
                ScreenToClient(GetHWnd(), &mousePos);  // ��ȡ��Դ��ڵ�λ��

                if (ui.isButtonClicked(mousePos.x, mousePos.y, WIDTH + 20, 50, WIDTH + 180, 100)) {
                    // ��ʼ��Ϸ��ť�����
                    break;
                }
            }
            Sleep(100);  // ����CPU����ռ��
        }

        BeginBatchDraw();  // ��ʼ˫�����ͼ
        while (true) {
            cleardevice();
            maze.drawMaze();
            ui.drawUI();
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
