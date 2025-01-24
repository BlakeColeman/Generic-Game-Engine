#pragma once
#include "rectangleShape.h";

#include <vector>


class compoundShape
{
protected:

    RECT Rect;
    COLORREF border;
    COLORREF fill;
    bool filled, isDragging, draggable;
    HDC hdc;
    POINT center;
    int borderWidth;

    std::vector <rectangleShape> elements;


public:
    // Constructors
    compoundShape(std::vector <rectangleShape> sElements,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc);

    compoundShape();

    // Setters
    //void setPositionByElements(int newLeft, int newTop, int newRight, int newBottom);
    void setRect();

    // Getters

    // Other methods
    bool isIn(POINT mouse);
    void draw();
};