#include "settingsButton.h"
#include "settingsWindow.h"

settingsButton::settingsButton(HDC sHdc, int sLeft, int sTop, int sRight, int sBottom, HICON sGear, WNDPROC sWindowProc, HWND sParent, int sWidth, int sHeight)
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
    buttonName = L"Settings";
    gear = sGear;
    windowProc = sWindowProc;
    parent = sParent;
    width = sWidth;
    height = sHeight;

    draw();
}

void settingsButton::doFunction()
{
    std::cout << "Settings Button Doing Stuff\n";
    settingsWindow(gear, L"Settings", windowProc, L"Settings", width, height, parent);
}

void settingsButton::draw()
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
    

    
    Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc,Brush);

    if ((gear == NULL))
    {

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
            DeleteObject(buttonFont);
    }
    else
    {
        DrawIcon(hdc, Rect.left + 8, Rect.top + 8 , gear);
    } 

    if (Brush)
    {
        DeleteObject(Brush);
    }
    DeleteObject(Pen);
}