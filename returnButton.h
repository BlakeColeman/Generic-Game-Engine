#pragma once
#include "Button.h"

class returnButton : public Button
{
private:
    int* curScreen;
public:
    // Constructor
    returnButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, int* sCurScreen, HWND sHwnd);

    // Other methods
    void doFunction() override;
};
