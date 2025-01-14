#pragma once
#include <windows.h>
#include <iostream>

class RectangleShape
{
protected:
    RECT Rect;
    COLORREF border;
    COLORREF fill;
    bool filled, isDragging, draggable;
    HDC hdc;
    int width;
    int height;
    POINT center;
    int borderWidth;

public:
    // Constructors
    RectangleShape(int sLeft, int sTop, int sRight, int sBottom,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc);
    RectangleShape(int sLeft, int sTop, int sRight, int sBottom,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc, int borderWidth);
    RectangleShape();

    // Setters
    void setPosition(int newLeft, int newTop, int newRight, int newBottom);
    void setBorderColor(COLORREF color);
    void setFillColor(COLORREF color);
    void setFilled(bool value);
    virtual void setPositionByCenter(POINT nCenter);
    void setIsDragging(bool value);

    // Getters
    POINT getCenter();
    int getLeft() const;
    int getTop() const;
    int getRight() const;
    int getBottom() const;
    int getDraggable() const;
    int getIsDragging() const;
    RECT getRect();

    // Other methods
    bool isIn(POINT mouse);
    virtual void draw();
};
