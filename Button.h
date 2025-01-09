#pragma once
#include "RectangleShape.h"

class Button : public RectangleShape
{
private:
    

public:
    const wchar_t* buttonName;
    // Constructor
    Button();
    Button(HDC sHdc, const wchar_t* sButtonName, int sTop, int sLeft, int sBottom, int sRight);
    
    // Other methods
    virtual void draw ();
    void destroyButton(HWND hwnd, HWND hwndButton);
    void updateButton();

    virtual void doFunction();
};