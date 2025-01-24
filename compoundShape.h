#pragma once
#include "rectangleShape.h";
#include <vector>


class compoundShape : public rectangleShape
{
protected:

    std::vector <rectangleShape> elements;

public:
    // Constructors
    compoundShape(std::vector <rectangleShape> sElements,
        COLORREF sBorder, COLORREF sFill, bool sFilled,
        bool draggable, HDC hdc);

    compoundShape();

    // Setters
    void setRect();
    void setPosition(int newLeft, int newTop, int newRight, int newBottom) override;
    void setPositionByCenter(POINT nCenter);

    // Getters

    // Other methods
    void draw() override;
    bool isIn(POINT point) override;
};