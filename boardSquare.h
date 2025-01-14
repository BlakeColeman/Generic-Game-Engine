#pragma once
#include "rectangleShape.h"


class boardSquare : public RectangleShape
{
private:
    bool full;

public:
    // Constructor
   boardSquare(int sLeft, int sTop, int sRight, int sBottom,
       COLORREF sBorder, COLORREF sFill, bool sFilled,
       bool draggable, HDC hdc);
    // Other methods
   void setFull(bool sFull);
   bool getFull();
};