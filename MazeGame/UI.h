#pragma once

enum Difficulty { EASY = 10, MEDIUM = 20, HARD = 30 };  // 确保在头文件中定义 Difficulty 枚举类型

class UI {
public:
    UI(int width, int height);
    void drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty);
    bool isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2);

private:
    int width, height;
};
