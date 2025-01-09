#pragma once
#include "Button.h"


class closeButton : public Button
{
private:

public:
    // Constructor
    closeButton(HDC sHdc, int sTop, int sLeft, int sBottom, int sRight);

    // Other methods
    void doFunction() override;
};