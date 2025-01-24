#include "polygonShape.h"

polygonShape::polygonShape(std::vector<POINT> sPoints, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc, int nBorderWidth)
{
	for (POINT point : sPoints)
	{
		points.push_back(point);
	}

	Rect.left = 0;
	Rect.top = 0;
	Rect.right = 0;
	Rect.bottom = 0;
	setRect();
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

void polygonShape::setPositionByCenter(POINT nCenter)
{
	int xChange = nCenter.x - center.x;
	int yChange = nCenter.y - center.y;

	std::vector<POINT> tempPoints;

	for (POINT point : points)
	{
		POINT newPoint;
		newPoint.x = point.x + xChange;
		newPoint.y = point.y + yChange;
		tempPoints.push_back(newPoint);
	}
	points.clear();
	for (POINT point : tempPoints)
	{
		points.push_back(point);
	}
	tempPoints.clear();

	center.x = nCenter.x;
	center.y = nCenter.y;

	setRect();
	draw();
}

void polygonShape:: setRect()
{
	int xMin = points[0].x;
	int xMax = points[0].x;
	int yMin = points[0].y;
	int yMax = points[0].y;

	for (POINT point : points)
	{
		if (point.x < xMin)  
		{
			xMin = point.x;
		}
		else if (point.x > xMax)
		{
			xMax = point.x;
		}

		if (point.y < yMin)
		{
			yMin = point.y;
		}
		else if (point.y > yMax)
		{
			yMax = point.y;
		}
	}

	Rect.left = xMin;
	Rect.right = xMax;
	Rect.top = yMin;
	Rect.bottom = yMax;
	center.x = xMax - (width/2);
	center.y = yMax - (height/2);
}

std::vector<POINT> polygonShape:: getPoints()
{
    return points;
}

void polygonShape::draw()
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

	Polygon(hdc, points.data(), points.size());

	if (Brush)
	{
		DeleteObject(Brush);
	}
	DeleteObject(Pen);
	return;
}
