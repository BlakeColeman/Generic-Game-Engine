#include "RectangleShape.h"

RectangleShape::RectangleShape()
{
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = 50;
	Rect.bottom = 50;
	fill = RGB(0, 0, 0);
	filled = true;
	border = RGB(0, 0, 0);
	draggable = 0;
	isDragging = false;
	center.x = Rect.right - Rect.left;
	center.y = Rect.bottom - Rect.top;
	borderWidth = 1;

	draw();
}

RectangleShape::RectangleShape(int sLeft, int sTop, int sRight, int sBottom, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable,HDC sHdc)
	{
		Rect.left = sLeft;
		Rect.top = sTop;
		Rect.right = sRight;
		Rect.bottom = sBottom;
		fill = sFill;
		filled = sFilled;
		border = sBorder;
		draggable = sDraggable;
		isDragging = false;
		hdc = sHdc;
		width = Rect.right - Rect.left;
		height = Rect.bottom - Rect.top;
		borderWidth = 1;

		draw();
	}

RectangleShape::RectangleShape(int sLeft, int sTop, int sRight, int sBottom, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc, int nBorderWidth)
{
	Rect.left = sLeft;
	Rect.top = sTop;
	Rect.right = sRight;
	Rect.bottom = sBottom;
	fill = sFill;
	filled = sFilled;
	border = sBorder;
	draggable = sDraggable;
	isDragging = false;
	hdc = sHdc;
	width = Rect.right - Rect.left;
	height = Rect.bottom - Rect.top;
	borderWidth = nBorderWidth;

	draw();
}

void RectangleShape:: setPosition(int newLeft, int newTop, int newRight, int newBottom)
	{
		Rect.left = newLeft;
		Rect.top = newTop;
		Rect.right = newRight;
		Rect.bottom = newBottom;
		draw();
	}

void RectangleShape:: setBorderColor(COLORREF color)
	{
		border = color;
		draw();
	}

void RectangleShape:: setFillColor(COLORREF color)
	{
		fill = color;
		draw();
	}

void RectangleShape:: setFilled(bool value)
	{
		filled = value;
		draw();
	}

bool RectangleShape:: isIn(POINT check)
{
	if ((check.x > Rect.left && check.x < Rect.right) && (check.y > Rect.top && check.y < Rect.bottom))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RectangleShape:: draw()
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

		Rectangle(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom);

		if (Brush)
		{
			DeleteObject(Brush);
		}
		DeleteObject(Pen);
		return;
	}

int RectangleShape:: getLeft() const
	{ 
		return Rect.left;
	}

int RectangleShape:: getTop() const
	{ 
		return Rect.top;
	}

int RectangleShape:: getRight() const
	{ 
		return Rect.right;
	}

int RectangleShape:: getBottom() const
	{ 
		return Rect.bottom;
	}

int RectangleShape:: getDraggable() const
	{
		return draggable;
	}

int RectangleShape:: getIsDragging() const
	{
		return isDragging;
	}

POINT RectangleShape::getCenter()
	{
		center.x = Rect.right - width/2;
		center.y = Rect.bottom - height/2;
		return center;
	}

void RectangleShape::setPositionByCenter(POINT nCenter)
{
	int xOffset = width / 2;
	int yOffset = height / 2;
	center = nCenter;
	setPosition(nCenter.x - xOffset,nCenter.y - yOffset, nCenter.x + xOffset, nCenter.y + yOffset);
}

void RectangleShape::setIsDragging(bool value)
{
	isDragging = value;
}

RECT RectangleShape::getRect()
{
	return Rect;
}