#include <graphics.h>
#include <conio.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include <tchar.h>  // ������ͷ�ļ�

#define WIDTH  800
#define HEIGHT 600
#define CELL_SIZE 20

int main() {
    initgraph(WIDTH + 200, HEIGHT); // ����UI����

    Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);
    maze.generateMaze(1, 1);

    UI ui(WIDTH, HEIGHT);
    ui.drawUI();

    Player player(maze, 1, 1);
    maze.drawMaze();

    BeginBatchDraw();  // ��ʼ˫�����ͼ
    while (true) {
        cleardevice();
        maze.drawMaze();
        ui.drawUI();
        player.drawPlayer();

        if (_kbhit()) {
            char input = _getch();
            player.movePlayer(input);
            if (player.isAtEnd()) {
                LPCTSTR message = _T("��Ӯ�ˣ�");
                outtextxy(WIDTH / 2 - 30, HEIGHT / 2, message);
                EndBatchDraw();  // ����˫�����ͼ
                break;
            }
        }

        FlushBatchDraw();  // ˢ�»�����
    }
    EndBatchDraw();  // ����˫�����ͼ

    _getch();
    closegraph();
    return 0;
}