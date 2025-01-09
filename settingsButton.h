#pragma once
#include "Button.h"


class settingsButton : public Button
{
private:

    HICON gear;
    WNDPROC windowProc;
    HWND parent;
    int height, width;

public:
    // Constructor
    settingsButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, HICON sGear, WNDPROC sWindowProc, HWND sParent, int sWidth, int sHeight);

    // Other methods
    //void drawWithIcon();
    void doFunction() override;
    void draw() override;
};