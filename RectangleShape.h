#pragma once
#include <windows.h>
#include <iostream>

class rectangleShape
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
    rectangleShape(int sLeft, int sTop, int sRight, int sBottom,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc);
    rectangleShape(int sLeft, int sTop, int sRight, int sBottom,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc, int borderWidth);
    rectangleShape(POINT sCenter, int sWidth, int sHeight);
    rectangleShape();

    // Setters
    virtual void setPosition(int newLeft, int newTop, int newRight, int newBottom);
    void setBorderColor(COLORREF color);
    void setFillColor(COLORREF color);
    void setFilled(bool value);
    virtual void setPositionByCenter(POINT nCenter);
    void setIsDragging(bool value);
    void setHDC(HDC sHdc);
    void setDraggable(bool value);

    // Getters
    POINT getCenter();
    int getLeft() const;
    int getTop() const;
    int getRight() const;
    int getBottom() const;
    int getDraggable() const;
    int getIsDragging() const;
    HDC getHdc() const;
    RECT getRect();

    // Other methods
    virtual bool isIn(POINT mouse);
    virtual void draw();
};