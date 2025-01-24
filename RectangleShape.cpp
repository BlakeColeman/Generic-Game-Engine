#include "rectangleShape.h"

rectangleShape::rectangleShape()
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

rectangleShape::rectangleShape(int sLeft, int sTop, int sRight, int sBottom, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable,HDC sHdc)
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

rectangleShape::rectangleShape(int sLeft, int sTop, int sRight, int sBottom, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc, int nBorderWidth)
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

rectangleShape::rectangleShape(POINT sCenter, int sWidth, int sHeight)
{
	Rect.left = sCenter.x - sWidth / 2;
	Rect.top = sCenter.y - sHeight / 2;
	Rect.right = sCenter.x + sWidth / 2;
	Rect.bottom = sCenter.y + sHeight / 2;
	fill = RGB(255,255,255);
	filled = true;
	border = RGB(0,0,0);
	draggable = false;
	isDragging = false;
	hdc = NULL;
	width = sWidth;
	height = sHeight;
	borderWidth = 1;

	draw();
}

void rectangleShape:: setPosition(int newLeft, int newTop, int newRight, int newBottom)
	{
		Rect.left = newLeft;
		Rect.top = newTop;
		Rect.right = newRight;
		Rect.bottom = newBottom;
		draw();
	}

void rectangleShape:: setBorderColor(COLORREF color)
	{
		border = color;
		draw();
	}

void rectangleShape:: setFillColor(COLORREF color)
	{
		fill = color;
		draw();
	}

void rectangleShape:: setFilled(bool value)
	{
		filled = value;
		draw();
	}

void rectangleShape::setHDC(HDC sHdc)
{
	hdc = sHdc;
}

bool rectangleShape:: isIn(POINT check)
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

void rectangleShape:: draw()
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

int rectangleShape:: getLeft() const
	{ 
		return Rect.left;
	}

int rectangleShape:: getTop() const
	{ 
		return Rect.top;
	}

int rectangleShape:: getRight() const
	{ 
		return Rect.right;
	}

int rectangleShape:: getBottom() const
	{ 
		return Rect.bottom;
	}

HDC rectangleShape:: getHdc() const
{
	return hdc;
}

int rectangleShape:: getDraggable() const
	{
		return draggable;
	}

void rectangleShape::setDraggable(bool value)
{
	draggable = value;
}

int rectangleShape:: getIsDragging() const
	{
		return isDragging;
	}

POINT rectangleShape::getCenter()
	{
		center.x = Rect.right - width/2;
		center.y = Rect.bottom - height/2;
		return center;
	}

void rectangleShape::setPositionByCenter(POINT nCenter)
{
	int xOffset = width / 2;
	int yOffset = height / 2;
	center = nCenter;
	setPosition(nCenter.x - xOffset,nCenter.y - yOffset, nCenter.x + xOffset, nCenter.y + yOffset);
}

void rectangleShape::setIsDragging(bool value)
{
	isDragging = value;
}

RECT rectangleShape::getRect()
{
	return Rect;
}