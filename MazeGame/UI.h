#pragma once

class UI {
public:
    UI(int width, int height);
    void drawUI();
    bool isButtonClicked(int mouseX, int mouseY, int btnX1, int btnY1, int btnX2, int btnY2);

private:
    int width, height;
};
