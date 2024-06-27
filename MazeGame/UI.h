#pragma once
#include "Common.h"

class UI {
public:
    UI(int width, int height);
    void drawStartUI(bool playerSelected, bool difficultySelected, bool playerMode, Difficulty difficulty);
    bool isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2);

private:
    int width, height;
};
