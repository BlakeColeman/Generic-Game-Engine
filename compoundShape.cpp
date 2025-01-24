#pragma once
#include "compoundShape.h";

// Constructors
compoundShape :: compoundShape(std::vector <rectangleShape> sElements, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc)
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

    borderWidth = 2;
    border = sBorder;
    for (rectangleShape element : sElements)
    {
        element.setBorderColor(sBorder);
        element.setFillColor(sFill);
        element.setFilled(sFilled);
        element.setDraggable(false);
        element.setHDC(hdc);
        element.setPositionByCenter(element.getCenter());
        element.draw();
        elements.push_back(element);
    }
    setRect();

}

bool compoundShape::isIn(POINT mouse)
{
    for (rectangleShape element : elements)
    {
        if (element.isIn(mouse))
        {
            return true;
        }
    }
    return false;
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
        element.draw();
    }

    if (Brush)
    {
        DeleteObject(Brush);
    }
    DeleteObject(Pen);
    return;
}

void compoundShape:: setPosition(int newLeft, int newTop, int newRight, int newBottom)
{
    POINT nCenter;
    nCenter.x = newRight - newLeft;
    nCenter.y = newBottom - newTop;
    setPositionByCenter(nCenter);
}

void compoundShape:: setPositionByCenter(POINT nCenter)
{
    int xChange, yChange;
    xChange = nCenter.x - center.x;
    yChange = nCenter.y - center.y;

    for (rectangleShape element : elements)
    {
        POINT elementCenter;
        elementCenter = element.getCenter();
        elementCenter.x = elementCenter.x + xChange;
        elementCenter.y = elementCenter.y + yChange;
        element.setPositionByCenter(elementCenter);
    }
}