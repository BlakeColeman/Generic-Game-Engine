#include "closeButton.h"

closeButton:: closeButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom)
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
    buttonName = L"Close Game";  

    draw();
}

void closeButton::doFunction()
{
    std::cout << "Close Button Doing Stuff\n";
    PostQuitMessage(0);
}