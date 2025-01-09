#pragma once
#include "appWindow.h"


class settingsWindow : public appWindow
{
private:
    HWND parent;

public:
    
    // Constructor
    settingsWindow(HICON sWindowIcon, const wchar_t* sWindowName, WNDPROC sWindowProc, const wchar_t* sWindowTitle, int sWidth, int sHeight, HWND sParent);
    
    // Other methods
    void create();
};