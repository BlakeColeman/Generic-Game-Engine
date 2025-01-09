#include "subReturnButton.h"

subReturnButton::subReturnButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, int* sCurScreen, HWND sHwnd)
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
    buttonName = L"Return to Menu";
    curScreen = sCurScreen;
    hwnd = sHwnd;
    draw();
}

void subReturnButton::doFunction()
{
    std::cout << "Return Button Doing Stuff\n";
    *curScreen = 0;
    DestroyWindow(hwnd);
}