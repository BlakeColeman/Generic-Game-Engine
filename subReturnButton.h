#pragma once
#include "Button.h"

class subReturnButton : public Button
{
private:
    int* curScreen;
    HWND hwnd;
public:
    // Constructor
    subReturnButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, int* sCurScreen, HWND sHwnd);

    // Other methods
    void doFunction() override;
};