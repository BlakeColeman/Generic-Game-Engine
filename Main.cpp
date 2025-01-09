#include <windows.h>
#include <iostream>
#include <vector>

#include "RectangleShape.h";
#include "Button.h";
#include "closeButton.h";
#include "playButton.h";
#include "settingsButton.h";
#include "returnButton.h";
#include "subReturnButton.h"
#include "appWindow.h";

#define TIMER_ID 1
#define TIMER_INTERVAL 16

RECT desktop;

//Icons Used by program
HICON gearIcon = (HICON)LoadImage(NULL, L"Gear.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

//Shape Vectors
std::vector<Button*> buttons;
std::vector<Button*> settingsButtons;
std::vector<RectangleShape*> rectangles;

bool leftButtonPressed = false;
bool rightButtonPressed = false;

bool levelRunning = false;
bool mainMenuRunning = false;

POINT mousePosition;

/*
Screen Directory:
Main Menu:      0,
Game Screen:    1,
*/

int curScreen = 0;
HWND hwndPlayButton, hwndCloseButton, hwndSettingsButton, hwndGearButton;
HWND hwndSubscreen = NULL;

//void onSettingsOpen(HWND hwnd, const wchar_t* subWindowClassName, WNDCLASS wc);
void createLevel(HDC hdc, HWND hwnd, int clientWidth, int clientHeight, SIZE textSize);
void updateLevel(HDC hdc, HWND hwnd, int clientWidth, int clientHeight, SIZE textSize);
void clearButtons();
void clearSettingsButtons();

// Window procedure for the settings subscreen
LRESULT CALLBACK SubWindowProc(HWND hwndSubscreen, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hwndParent = GetParent(hwndSubscreen);
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            hwndSubscreen = NULL;
            clearSettingsButtons();
            return 0;
        }
        case WM_CLOSE:
        {
            DestroyWindow(hwndSubscreen);
            clearSettingsButtons();
            hwndSubscreen = NULL;
            return 0;
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwndSubscreen, &ps);
            RECT rect;
            GetClientRect(hwndSubscreen, &rect);
            int windowWidth = rect.right - rect.left;
            int windowHeight = rect.bottom - rect.top;
            SIZE textSize;
            const wchar_t* settingsText = L"Settings Subscreen";
            GetTextExtentPoint32(hdc, settingsText, wcslen(settingsText), &textSize);;
            int x = (rect.right - rect.left - textSize.cx) / 2;
            int y = (rect.bottom - rect.top - textSize.cy) / 2;
            SetTextColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, x, y, settingsText, wcslen(settingsText));

            Button* returnMenuButton = new subReturnButton(hdc, windowWidth / 2 - 250, windowHeight - 250, windowWidth / 2 - 10, windowHeight - 200, &curScreen, hwndSubscreen);
            Button* closeGameButton = new closeButton(hdc, ((windowWidth/2)+10), ((windowHeight) - 250), (windowWidth/2) + 250 ,windowHeight - 200);

            settingsButtons.push_back(returnMenuButton);
            settingsButtons.push_back(closeGameButton);


            EndPaint(hwndSubscreen, &ps);
            return 0;
        }

        case WM_COMMAND:
        {
            if (LOWORD(wParam) == 11) // Close Game Button
            {
                DestroyWindow(hwndSubscreen);
                hwndSubscreen = NULL;
                PostQuitMessage(0);
                return 0;
            }
            else if (LOWORD(wParam) == 12) //Return Button
            {
                curScreen = 0;
                ShowWindow(hwndParent, SW_SHOW);
                SetForegroundWindow(hwndParent);
                DestroyWindow(hwndSubscreen);
                hwndSubscreen = NULL;
                InvalidateRect(hwndParent, NULL, TRUE);
                return 0;
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {

            leftButtonPressed = true; // Left mouse button down
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwndSubscreen, &pt);

            for (Button* button : settingsButtons)
            {
                if (button->isIn(pt))
                {
                    button->doFunction();
                    return true;  // Mouse is inside this rectangle
                }
            }

            return 0;
        }
    }
    return DefWindowProc(hwndSubscreen, uMsg, wParam, lParam);
}

// Window procedure function to process events like closing the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;
    static HDC hdcMem = NULL;
    static HBITMAP hBitmap = NULL;
    SIZE textSize = {0,0};
    int fontsize = (clientWidth) / 20;   
    HFONT hFont = CreateFont(fontsize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
    SelectObject(hdcMem, hFont);

    switch (uMsg)
    {            
        case WM_CREATE:
        {
            HDC hdc = GetDC(hwnd);
            hdcMem = CreateCompatibleDC(hdc);
            hBitmap = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);  // Use the window's client area size
            SelectObject(hdcMem, hBitmap);
            ReleaseDC(hwnd, hdc);
            return 0;
        }

        case WM_DESTROY:
        {
            DeleteDC(hdcMem);
            DeleteObject(hBitmap);
            PostQuitMessage(0);  // Send a message to quit the application
            return 0;
        }
        
        case WM_COMMAND:
        {
          // Check if the button was clicked
          if (LOWORD(wParam) == 1) { // 1 is the ID of the button
            // play screen
            curScreen = 1;
            ShowWindow(hwndPlayButton, SW_HIDE);
            ShowWindow(hwndSettingsButton, SW_HIDE);
            ShowWindow(hwndCloseButton, SW_HIDE);
            ShowWindow(hwndGearButton, SW_SHOW);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
          else if (LOWORD(wParam) == 2)
        {
            PostQuitMessage(0);
            return 0;
        }
          break;
        }

        case WM_LBUTTONDOWN:
        {        

            leftButtonPressed = true; // Left mouse button down
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            for (Button* button : buttons)
            {
                if (button->isIn(pt))
                {   
                    button->doFunction();
                    InvalidateRect(hwnd, NULL, FALSE);
                }
            }

            for (RectangleShape* rectangle : rectangles)
            {
                RECT rect;
                rect = rectangle->getRect();
                std::cout << "\nMouse is in Location:" << mousePosition.x << "," << mousePosition.y;
                std::cout << "\nRectangle Points: \tLeft:" << rect.left << "\tTop" << rect.top << "\tRight" << rect.right << "\tBottom" << rect.bottom;
                std::cout << "\nChecking if Mouse is in Rectangle";
                if (rectangle->isIn(mousePosition))
                {
                    std::cout << "\nMouse is in Rectangle";
                    std::cout << "\nIs Rectangle Draggable: " << rectangle->getDraggable();
                    if (rectangle->getDraggable())
                    {
                        rectangle->setIsDragging(true);
                    }
                    std::cout << "\nIs Rectangle dragging: " << rectangle->getIsDragging();
                }
            }
            return 0;
        }

        case WM_RBUTTONDOWN:  // Right mouse button down
    {
        rightButtonPressed = true;
        return 0;
    }

        case WM_LBUTTONUP:  // Left mouse button up
        {
            for (RectangleShape* rectangle : rectangles)
            {
                rectangle->setIsDragging(false);
            }
            leftButtonPressed = false;
            return 0;
        }

        case WM_RBUTTONUP:  // Right mouse button up
    {
        rightButtonPressed = false;
        return 0;
    }

        case WM_MOUSEMOVE:
        {
            POINT screenPos;
            if (GetCursorPos(&screenPos))
            {
                ScreenToClient(hwnd, &screenPos);
                mousePosition = screenPos;
            }
        
            for (RectangleShape* rectangle : rectangles)
            {
                if (rectangle->getIsDragging())
                {
                    rectangle->setPositionByCenter(mousePosition);
                }
                //std::cout << "\n Rectangle Draggable:" <<rectangle->getDraggable();
                //std::cout << "\n Rectangle Dragging: " << rectangle->getIsDragging();
            }
        }

        case WM_PAINT:
        {

            //Painting the text on the window
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps); // Start painting

            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);
            FillRect(hdcMem, &rect, (HBRUSH)(COLOR_WINDOW + 1));

            //Decide which screen to load into memory
            switch (curScreen) 
            {
                case 0:
                {
                    if (!mainMenuRunning)
                    {
                        if (buttons.size() != 0)
                        {
                            clearButtons();
                        }

                        Button* playGameButton = new playButton(hdcMem, ((clientWidth / 2) - 200), ((clientHeight / 2) + 115), ((clientWidth / 2) + 200), ((clientHeight / 2) + 165), &curScreen);
                        Button* settingsWindowButton = new settingsButton(hdcMem, ((clientWidth / 2) + 5), ((clientHeight / 2) + 175), ((clientWidth / 2) + 200), ((clientHeight / 2) + 225),NULL, SubWindowProc,hwnd, clientWidth*0.75, clientHeight*0.75);
                        Button* closeGameButton = new closeButton(hdcMem, ((clientWidth / 2) - 200), ((clientHeight / 2) + 175), ((clientWidth / 2) - 5), ((clientHeight / 2) + 225));

                        buttons.push_back(playGameButton);
                        buttons.push_back(settingsWindowButton);
                        buttons.push_back(closeGameButton);  
                    }
                    else
                    {
                        for (Button* button : buttons)
                        {
                            button->draw();
                        }
                    }
                        int x;
                        int y;

                        DrawIcon(hdcMem, clientWidth - 60, 10, gearIcon);

                        // Set the text to display
                        const wchar_t* menuText = L"Generic Puzzle Game!";

                        // Get the dimensions of the text to center it
                        GetTextExtentPoint32(hdcMem, menuText, wcslen(menuText), &textSize);

                        //Calculate the position to center the text
                        x = (clientWidth - textSize.cx) / 2; // Center horizontally
                        y = (clientHeight - textSize.cy) / 2; // Center vertically

                        // Set the text color to Black
                        SetTextColor(hdcMem, RGB(0, 0, 0));

                        // Draw the text in the middle of the window
                        TextOut(hdcMem, x, y, menuText, wcslen(menuText));

                        levelRunning = false;
                        mainMenuRunning = true;

                    break;
                }
                case 1:
                {
                    if (!levelRunning)
                    {
                        createLevel(hdcMem, hwnd, clientWidth, clientHeight, textSize);
                        mainMenuRunning = false;
                    }
                    else
                    {
                        updateLevel(hdcMem, hwnd, clientWidth, clientHeight, textSize);
                    }
                    break;
                }
            }

            BitBlt(hdc, 0, 0, clientWidth, clientHeight, hdcMem, 0, 0, SRCCOPY);
            SetBkMode(hdc, TRANSPARENT);

            EndPaint(hwnd, &ps); // End painting

            return 0;
        }

        case WM_TIMER:
        {
            UpdateWindow(hwnd); 
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);  // Default window processing
}

int main() {
    // Registering the window class
    const wchar_t* className = L"MyWindowClass"; // Use wide string (L"")
    const wchar_t* windowTitle = L"Generic Puzzle Game!"; // Use wide string (L"")
    HICON GPGI = (HICON)LoadImage(NULL, L"GPG.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

    // Step 2: Get the Screen resolution
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right;
    int screenHeight = desktop.bottom;

    appWindow gameWindow(GPGI, className, WindowProc, windowTitle, screenWidth,screenHeight);
    WNDCLASS wc = gameWindow.getWndClass();

    // Step 3: Create the main window
    HWND hwnd = gameWindow.getHWND();

    //SendMessage(hwndGearButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hGearIcon);
    //InvalidateRect(hwndGearButton, NULL, TRUE);
    
    SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);

    // Step 5: Show the window
    ShowWindow(hwnd, SW_SHOW);

    // Step 6: Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;

    KillTimer(hwnd, TIMER_ID);

}

void invalidateButton(HWND hwnd, HWND hwndButton)
{
    RECT buttonRect;
    GetClientRect(hwndButton, &buttonRect);  // Get button's current position
    InvalidateRect(hwnd, &buttonRect, FALSE);  // Only invalidate the button area
    UpdateWindow(hwnd);  // Force immediate repaint
}

void createLevel(HDC hdc,HWND hwnd, int clientWidth, int clientHeight, SIZE textSize)
{
    clearButtons();
    
    int x;
    int y;
    // Set the text to display
    const wchar_t* gameText = L"Play Screen!";

    RECT rect;
    GetClientRect(hwnd, &rect);

    // Get the dimensions of the text to center it
    GetTextExtentPoint32(hdc, gameText, wcslen(gameText), &textSize);

    //Calculate the position to center the text
    x = (clientWidth - textSize.cx) / 2; // Center horizontally
    y = (clientHeight - textSize.cy) / 2; // Center vertically

    // Set the text color
    SetTextColor(hdc, RGB(0, 0, 0)); // Black color

    // Set the background mode to transparent
    SetBkMode(hdc, TRANSPARENT);

    // Draw the text in the middle of the window
    TextOut(hdc, x, y, gameText, wcslen(gameText));

    RectangleShape* firstRectangle = new RectangleShape(100,100,200,200,RGB(0,0,0),RGB(255,255,255),false,true,hdc);
    
    rectangles.push_back(firstRectangle);

    Button* gearButton = new settingsButton(hdc, clientWidth-60, 10, clientWidth -10, 60, gearIcon, SubWindowProc, hwnd, clientWidth * 0.75, clientHeight * 0.75);
    
    buttons.push_back(gearButton);

    levelRunning = true;

    return;
}

void updateLevel(HDC hdc, HWND hwnd, int clientWidth, int clientHeight, SIZE textSize)
{
    
    int x;
    int y;
    
    // Set the text to display
    const wchar_t* gameText = L"Play Screen!";

    RECT rect;
    GetClientRect(hwnd, &rect);
    
    // Get the dimensions of the text to center it
    GetTextExtentPoint32(hdc, gameText, wcslen(gameText), &textSize);

    //Calculate the position to center the text
    x = (clientWidth - textSize.cx) / 2; // Center horizontally
    y = (clientHeight - textSize.cy) / 2; // Center vertically

    // Set the text color
    SetTextColor(hdc, RGB(0, 0, 0)); // Black color

    // Set the background mode to transparent
    SetBkMode(hdc, TRANSPARENT);
 
    // Draw the text in the middle of the window
    TextOut(hdc, x, y, gameText, wcslen(gameText));
 
    for (Button* button : buttons)
    {
        button->draw();
    }
    
    for (RectangleShape* rectangle : rectangles)
    {
        rectangle->draw();
        RECT rect = rectangle->getRect();
        InvalidateRect(hwnd, &rect, FALSE);
        //std::cout << "Rectangle Drawn\n";
    }
    InvalidateRect(hwnd, NULL, FALSE);
}

void updateScreen()
{

}

void clearButtons()
{
    if (buttons.size() != 0)
    {
        Button* toDelete;
        for (Button* button : buttons)
        {
            delete button;
        }
        buttons.clear();
    }
}

void clearSettingsButtons()
{
    if (buttons.size() != 0)
    {
        Button* toDelete;
        for (Button* button : settingsButtons)
        {
            delete button;
        }
        settingsButtons.clear();
    }
}