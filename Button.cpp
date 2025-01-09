#include "Button.h"
#include <iostream>

Button::Button()
{
    Rect.left = 0;
    Rect.top = 0;
    Rect.right = 50;
    Rect.bottom = 50;
    fill = RGB(200, 200, 200);
    filled = true;
    border = RGB(0, 0, 0);
    draggable = false;
    isDragging = false;
    buttonName = L"PlaceHolder";
}

Button:: Button(HDC sHdc, const wchar_t* sButtonName, int sLeft, int sTop, int sRight, int sBottom)
{
    Rect.left = sLeft;
    Rect.top = sTop;
    Rect.right = sRight;
    Rect.bottom = sBottom;
    fill = RGB(200, 200, 200);
    filled = true;
    border = RGB(0,0,0);
    draggable = false;
    isDragging = false;
    hdc = sHdc;
    buttonName = sButtonName;

    draw();
}

void Button:: draw()
{
    HFONT buttonFont;
    HPEN Pen = CreatePen(PS_SOLID, 1, border);
    SelectObject(hdc, Pen);

    HBRUSH Brush = nullptr;
    if (filled)
    {
        Brush = CreateSolidBrush(fill);
        SelectObject(hdc, Brush);
    }

    Rectangle(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom);

    if (Brush)
    {
        DeleteObject(Brush);
    }
    DeleteObject(Pen);


    int fontSize = ((Rect.bottom - Rect.top) * 0.5);

    buttonFont = CreateFont(
        -MulDiv(fontSize, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 75), // Font size in pixels
        0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS, L"Arial");

    SetTextColor(hdc, RGB(0, 0, 0)); // White text
    SetBkMode(hdc, TRANSPARENT);

    HFONT tempFont = (HFONT)SelectObject(hdc, buttonFont);

    DrawText(hdc, buttonName, -1, &Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hdc, tempFont);
    DeleteObject(Pen);
    DeleteObject(buttonFont);
}

void Button:: updateButton()
{

}

void Button:: destroyButton(HWND hwnd, HWND hwndButton)
{
    RECT buttonRect;
    GetClientRect(hwndButton, &buttonRect);  // Get button's current position
    InvalidateRect(hwnd, &buttonRect, FALSE);  // Only invalidate the button area
    UpdateWindow(hwnd);  // Force immediate repaint
}

void Button::doFunction()
{
    std::cout << "Button Doing Stuff\n";
}