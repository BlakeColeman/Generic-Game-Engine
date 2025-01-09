#pragma once
#include <windows.h>
#include <iostream>

class appWindow
{
protected:
    const wchar_t* windowName;
    const wchar_t* windowTitle;
    HICON windowIcon;
    WNDCLASS wc;
    WNDPROC windowProc;
    HWND hwnd;
    int width;
    int height;

public:
    // Constructors
    appWindow(HICON sWindowIcon, const wchar_t* sWindowName, WNDPROC sWindowProc, const wchar_t* sWindowTitle, int sWidth, int sHeight);
    appWindow();

    //getters
    WNDCLASS getWndClass();
    HWND getHWND();

    // Other methods
    void create();
    void focus();
};