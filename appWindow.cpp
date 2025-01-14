#pragma once
#include "appWindow.h";

appWindow:: appWindow(HICON sWindowIcon, const wchar_t* sWindowName, WNDPROC sWindowProc, const wchar_t* sWindowTitle, int sWidth, int sHeight)
{
    windowIcon = sWindowIcon;
    windowName = sWindowName;
    windowProc = sWindowProc;
    windowTitle = sWindowTitle;
    width = sWidth;
    height = sHeight;
    hwnd = NULL;
    wc.lpfnWndProc = windowProc;         // Window procedure function
    wc.hInstance = GetModuleHandle(nullptr); // Get the instance handle
    wc.lpszClassName = windowName;        // Window class name (wide string)
    wc.style = CS_HREDRAW | CS_VREDRAW;            // Redraw window on size changes
    wc.cbClsExtra = 0;                             // No extra data
    wc.cbWndExtra = 0;                             // No extra data
    wc.hIcon = windowIcon;                         // Setting icon
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);   // Default cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background color

    if (RegisterClass(&wc) == 0) 
    {
        DWORD dwError = GetLastError();
        std::cerr << "Window class registration failed with error code " << dwError << std::endl;
    }
    create();
}

appWindow::appWindow()
{
    windowName = L"DefaultWindow";
    windowTitle = L"DefaultWindow";
    windowIcon = NULL;
    wc = {};
    windowProc = NULL;
    hwnd = NULL;
    width = 750;
    height = 750;
}

void appWindow::create()
{
    // Step 3: Create the main window
    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,                            // Window styles
        windowName,                                 // Window class name (wide string)
        windowTitle,                                // Window title (wide string)
        WS_POPUP | WS_VISIBLE,                      // Window style
        0, 0, width, height,                        // Position and size
        nullptr,                                    // Parent Window 
        nullptr,                                    // Menu
        wc.hInstance,                               // Instance handle
        nullptr                                     // Additional Parameters
    );
}

WNDCLASS appWindow:: getWndClass()
{
    return wc;
}

HWND  appWindow::getHWND()
{
    return hwnd;
}

void appWindow::focus()
{
    SetForegroundWindow(hwnd);
}