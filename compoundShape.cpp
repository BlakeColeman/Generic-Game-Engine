#pragma once
#include "compoundShape.h";

// Constructors
compoundShape :: compoundShape(std::vector <rectangleShape> sElements,
    COLORREF sBorder, COLORREF sFill, bool sFilled,
    bool sDraggable, HDC sHdc)
{
    border = sBorder;
    fill = sFill;
    filled = sFilled;
    draggable = sDraggable;
    hdc = sHdc;
    
    Rect.left = 0;
    Rect.top = 0;
    Rect.right = 0;
    Rect.bottom = 0;
    setRect();

    borderWidth = 2;

    border = sBorder;


    for (rectangleShape element : elements)
    {
        element.setBorderColor(sBorder);
        element.setFillColor(sFill);
        element.setFilled(sFilled);
        element.setDraggable(draggable);
        element.setHDC(hdc);
        element.setPositionByCenter(element.getCenter());
        element.draw();
    }

}

//std::vector <rectangleShape> elements;

bool compoundShape::isIn(POINT mouse)
{
    for (rectangleShape element : elements)
    {
        if (element.isIn(mouse))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void compoundShape:: setRect()
{

    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    POINT temp = elements.front().getCenter();
    maxX = temp.x;
    maxY = temp.y;

    for (rectangleShape element : elements)
    {
        temp = element.getCenter();

        if (temp.x < minX)
        {
            minX = temp.x;
        }
        else if (temp.x > maxX)
        {
            maxX = temp.x;
        }

        if (temp.y < minY)
        {
            minY = temp.y;
        }
        else if (temp.y > maxY)
        {
            maxY = temp.y;
        }
    }
}

void compoundShape:: draw()
{
    SetBkMode(hdc, TRANSPARENT);

    HPEN Pen = CreatePen(PS_SOLID, borderWidth, border);
    SelectObject(hdc, Pen);

    HBRUSH Brush = nullptr;
    if (filled)
    {
        Brush = CreateSolidBrush(fill);
    }
    else
    {
        Brush = CreateSolidBrush(RGB(255, 255, 255));
    }
    SelectObject(hdc, Brush);

    for (rectangleShape element : elements)
    {
        RECT Rect = element.getRect();
        Rectangle(element.getHdc(), Rect.left, Rect.top, Rect.right, Rect.bottom);
    }

    if (Brush)
    {
        DeleteObject(Brush);
    }
    DeleteObject(Pen);
    return;
}




