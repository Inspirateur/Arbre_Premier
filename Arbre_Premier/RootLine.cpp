#include "RootLine.h"

RootLine::RootLine(int x, int y):
	Line::Line(0, -01.57079, 0, this)
{
	x1 = float(x);
	y1 = float(y);
	Line::setX1(&x1);
	Line::setY1(&y1);
	updatePoint2();
}

void RootLine::setX1(int x) {
	x1 = float(x);
}

void RootLine::setY1(int y) {
	y1 = float(y);
}
