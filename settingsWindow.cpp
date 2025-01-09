#include "settingsWindow.h"
#include "closeButton.h"


settingsWindow::settingsWindow(HICON sWindowIcon, const wchar_t* sWindowName, WNDPROC sWindowProc, const wchar_t* sWindowTitle, int sWidth, int sHeight, HWND sParent)
{
    windowIcon = sWindowIcon;
    windowName = sWindowName;
    windowProc = sWindowProc;
    windowTitle = sWindowTitle;
    width = sWidth;
    height = sHeight;
    parent = sParent;
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
        std::cerr << "Settings Window class registration failed with error code " << dwError << std::endl;
    }

    create();
}

void settingsWindow::create()
{
    if (hwnd == NULL || !IsWindow(hwnd))
    {
        hwnd = CreateWindowEx
        (
            WS_EX_APPWINDOW,
            windowName,
            windowTitle,
            WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX | WS_VISIBLE, // Window style
            width-(width*0.85),height-(height*0.85), width, height, // Position and size
            parent,  // Parent window (the main window)
            nullptr, // No menu
            wc.hInstance, // Instance handle
            nullptr  // No additional parameters
        );
    }
}