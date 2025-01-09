#pragma once
#include "Button.h"


class playButton : public Button
{
private:
    int* curScreen;

public:
    // Constructor
    playButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, int* sCurScreen);

    // Other methods
    void doFunction() override;
};