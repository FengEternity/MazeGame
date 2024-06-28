#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "Maze.h"
#include "Player.h"
#include "UI.h"
#include "Common.h"
#include <tchar.h>
#include <iostream>  // ���ڵ������
#include <thread>    // ��������ӳ�
#include <chrono>    // ��������ӳ�

#pragma comment(lib, "winmm.lib")  // ���ӵ�winmm.lib

#define CELL_SIZE 20  // �����Թ���Ԫ��Ĵ�С

void playSound(const char* filename, bool loop = false) {
    char command[256];
    sprintf_s(command, "open %s alias %s", filename, filename);

    // �� command ת��Ϊ���ַ��ַ���
    wchar_t wCommand[256];
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // ʹ�ÿ��ַ��ַ������� mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);

    sprintf_s(command, "play %s", filename);
    if (loop) {
        strcat_s(command, " repeat");
    }

    // �ٴ�ת�� command Ϊ���ַ��ַ���
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // ʹ�ÿ��ַ��ַ������� mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);
}

void stopSound(const char* filename) {
    char command[256];
    sprintf_s(command, "close %s", filename);

    // �� command ת��Ϊ���ַ��ַ���
    wchar_t wCommand[256];
    MultiByteToWideChar(CP_ACP, 0, command, -1, wCommand, 256);

    // ʹ�ÿ��ַ��ַ������� mciSendStringW
    mciSendStringW(wCommand, NULL, 0, NULL);
}

void showVictoryMessage(int width, int height);
void showOptions(int width, int height, bool& playAgain, bool& goToStart, bool& exitGame);

int main() {
    const int initialRows = 30, initialCols = 30;  // ��ʼ������
    const int initialWidth = initialCols * CELL_SIZE;  // ��ʼ���ڿ��
    const int initialHeight = initialRows * CELL_SIZE;  // ��ʼ���ڸ߶�

    Difficulty difficulty = MEDIUM;  // ��ʼ���Ѷ�Ϊ�е�
    bool playerMode = true;  // ��ʼ��Ϊ���ģʽ
    bool playerSelected = false;  // ���ģʽ�Ƿ���ѡ��
    bool difficultySelected = false;  // �Ѷ��Ƿ���ѡ��

    int rows = initialRows, cols = initialCols;  // Ĭ��������
    int width = initialWidth;  // ���ڿ��
    int height = initialHeight;  // ���ڸ߶�

    // ��ʼ��ͼ�ν��棬���ô��ڴ�С
    initgraph(width, height);
    UI ui(width, height);  // ����UI���󣬴��봰�ڿ�Ⱥ͸߶�

    bool playAgain = false;  // �Ƿ����¿�ʼ��Ϸ�ı�־
    bool goToStart = true;  // �Ƿ񷵻ؿ�ʼ����ı�־
    bool exitGame = false;   // �Ƿ��˳���Ϸ�ı�־

    // ���ű�������
    // playSound("background_music.mp3", true);

    // ��ѭ��������Ϸ�߼�
    while (true) {
        // ��ʾ��Ϸ��ʼ���沢�����û�ѡ��
        while (goToStart || (!playerSelected || !difficultySelected)) {
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
                    goToStart = false;
                    // ������Ϸ��ʼ��Ч
                    playSound("start_game.mp3");
                    playSound("background_music.mp3", true);
                    break;  // ��ʼ��Ϸ������ѭ��
                }
            }
            Sleep(100);  // ����CPU����ռ��
        }

        // ����ѡ����Ѷȵ������ڴ�С
        width = cols * CELL_SIZE;
        height = rows * CELL_SIZE;
        initgraph(width, height);  // ���³�ʼ��ͼ�ν��棬���ô��ڴ�С

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
                    playSound("move.wav");  // �����ƶ���Ч
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    player.movePlayer('s');
                    playSound("move.wav");  // �����ƶ���Ч
                }
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    player.movePlayer('a');
                    playSound("move.wav");  // �����ƶ���Ч
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    player.movePlayer('d');
                    playSound("move.wav");  // �����ƶ���Ч
                }
            }
            else {
                // ����ģʽ���Զ��ƶ����
                player.autoMove();
                playSound("auto_move.wav");  // �����Զ��ƶ���Ч
            }

            if (player.hasMoved()) {  // ��������ƶ�ʱ���������Ϣ
                std::cout << "Drawing player at (" << player.getX() << ", " << player.getY() << ").\n";
            }

            if (player.isAtEnd()) {
                // ��ҵ����յ㣬��ʾʤ����Ϣ
                stopSound("background_music.mp3");
                playSound("victory.mp3");  // ����ʤ����Ч
                showVictoryMessage(width, height);  // ��ʾ����Ӯ�ˣ�����Ϣ
                std::cout << "Player reached the end.\n";  // ���������Ϣ
                break;
            }

            FlushBatchDraw();  // ˢ�»�����
            Sleep(50);  // ����ӳ��Ա������ռ��CPU
        }
        EndBatchDraw();  // ����˫�����ͼ

        // �ȴ��û�ѡ��������˳�
        showOptions(width, height, playAgain, goToStart, exitGame);

        if (exitGame) {
            break;  // �˳���Ϸ
        }

        if (!playAgain && !goToStart) {
            break;  // ��������¿�ʼ��Ҳ���ص���ҳ�����˳�ѭ��
        }

        // �رյ�ǰͼ�ν���
        closegraph();

        if (goToStart) {
            // ���ô��ڴ�СΪ��ʼ״̬
            width = initialWidth;
            height = initialHeight;
            rows = initialRows;
            cols = initialCols;
            initgraph(width, height);  // ���³�ʼ��ͼ�ν��棬���ô��ڴ�С
            ui = UI(width, height);  // ���´���UI����
        }
        else {
            // ���³�ʼ��ͼ�ν��棬ȷ������������ʱ��ʾ����
            initgraph(width, height);
            ui = UI(width, height);  // ���´���UI����
        }
    }

    // ֹͣ��������
    // stopSound("background_music.mp3");

    closegraph();  // �ر�ͼ�ν���
    return 0;
}

void showVictoryMessage(int width, int height) {
    cleardevice();
    settextstyle(40, 0, _T("Arial"));  // ����������ʽ
    settextcolor(WHITE);
    outtextxy(width / 2 - 100, height / 2 - 20, _T("��Ӯ�ˣ�"));
    FlushBatchDraw();
    std::this_thread::sleep_for(std::chrono::seconds(3));  // ��ʾ3����
}

void showOptions(int width, int height, bool& playAgain, bool& goToStart, bool& exitGame) {
    cleardevice();
    settextstyle(30, 0, _T("Arial"));
    settextcolor(WHITE);

    // ���ư�ť
    solidrectangle(width / 2 - 100, height / 2, width / 2 + 100, height / 2 + 30);
    solidrectangle(width / 2 - 100, height / 2 + 40, width / 2 + 100, height / 2 + 70);
    solidrectangle(width / 2 - 100, height / 2 + 80, width / 2 + 100, height / 2 + 110);

    // ���ư�ť�ı�
    outtextxy(width / 2 - 60, height / 2 + 5, _T("���¿�ʼ"));
    outtextxy(width / 2 - 60, height / 2 + 45, _T("�ص���ҳ"));
    outtextxy(width / 2 - 60, height / 2 + 85, _T("�˳���Ϸ"));
    FlushBatchDraw();

    while (true) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {  // ������������
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(GetHWnd(), &mousePos);  // ��ȡ�����λ�ã�ת��Ϊ��������

            if (mousePos.x > width / 2 - 100 && mousePos.x < width / 2 + 100) {
                if (mousePos.y > height / 2 && mousePos.y < height / 2 + 30) {
                    playAgain = true;
                    goToStart = false;
                    exitGame = false;
                    break;
                }
                if (mousePos.y > height / 2 + 40 && mousePos.y < height / 2 + 70) {
                    playAgain = false;
                    goToStart = true;
                    exitGame = false;
                    break;
                }
                if (mousePos.y > height / 2 + 80 && mousePos.y < height / 2 + 110) {
                    playAgain = false;
                    goToStart = false;
                    exitGame = true;
                    break;
                }
            }
        }
        Sleep(100);  // ����CPU����ռ��
    }
}
