#pragma once
#include "rectangleShape.h"
#include <vector>


class polygonShape : public RectangleShape
{
private:

   std:: vector<POINT> points;
   POINT center;

public:
    // Constructor
   polygonShape(std::vector<POINT>, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc, int nBorderWidth);
   


   //Setters
   void setPositionByCenter(POINT nCenter) override;
   void setRect();

   //Getters
   std::vector<POINT> getPoints();

   // Other methods
   void draw() override;

};