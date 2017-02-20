#pragma once
#include "Line.h"

class RootLine : public Line {
public:
	RootLine(int x, int y);
	void setX1(int x);
	void setY1(int y);
	inline float getAngle() const { return a; }

private:
	float x1;
	float y1;
};