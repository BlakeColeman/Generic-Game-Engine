#include "boardSquare.h"

boardSquare::boardSquare(int sLeft, int sTop, int sRight, int sBottom, COLORREF sBorder, COLORREF sFill, bool sFilled, bool sDraggable, HDC sHdc)
{
	Rect.left = sLeft;
	Rect.top = sTop;
	Rect.right = sRight;
	Rect.bottom = sBottom;
	fill = sFill;
	filled = false;
	border = sBorder;
	draggable = false;
	isDragging = false;
	hdc = sHdc;
	width = Rect.right - Rect.left;
	height = Rect.bottom - Rect.top;
	borderWidth = 5;
	full = false;

	draw();
}

void  boardSquare:: setFull(bool sFull)
{
	full = sFull;
}

bool boardSquare:: getFull()
{
	return full;
}
