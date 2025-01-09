#include "playButton.h"

playButton::playButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, int* sCurScreen)
{
    Rect.left = sLeft;
    Rect.top = sTop;
    Rect.right = sRight;
    Rect.bottom = sBottom;
    fill = RGB(200, 200, 200);
    filled = true;
    border = RGB(0, 0, 0);
    draggable = false;
    isDragging = false;
    hdc = sHdc;
    buttonName = L"Play";
    curScreen = sCurScreen;
    draw();
}

void playButton::doFunction()
{
    std::cout << "Play Button Doing Stuff\n";
    *curScreen = 1;
}