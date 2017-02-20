#include "Line.h"
#include <cmath>
#include <iostream>

Line::Line(float* x, float* y, float length, float angle, int rank, Line* parent_Line):
	x1(x),
	y1(y),
	l(length),
	a(angle),
	r(rank),
	parentLine(parent_Line),
	color(sf::Color(150-5*rank, 75+30*rank, 10+2*rank))
{
	graphicalNode = sf::CircleShape(4);
	graphicalNode.setOutlineThickness(3);
	graphicalNode.setFillColor(*(parentLine->getColor()));
	graphicalNode.setOutlineColor(color);
	graphicalNode.setOrigin(4, 4);
	graphicalLine.setOrigin(0, 2);
}

//SECTION FOR ROOTLINE USE------------------------------------
Line::Line(float length, float angle, int rank, Line* parent_Line) :
	Line::Line(nullptr, nullptr, length, angle, rank, parent_Line)
{}

void Line::setX1(float* x) {
	x1 = x;
}

void Line::setY1(float* y) {
	y1 = y;
}
//END OF SECTION FOR ROOTLINE USE-----------------------------

void Line::setL(float length) {
	l = length;
	updatePoint2();
}

void Line::setA(float angle) {
	a = angle;
	updatePoint2();
}

void Line::addL(float length) {
	l += length;
	updatePoint2();
}

void Line::updatePoint2() {
	x2 = (*x1) + l*cos(a+parentLine->getAngle());
	y2 = (*y1) + l*sin(a+parentLine->getAngle());
	graphicalLine.setPosition(getX1(), getY1());
	graphicalLine.setSize(sf::Vector2f(l, 4));
	graphicalLine.setRotation((a + parentLine->getAngle())*180/3.14159265359);
	graphicalNode.setPosition(getX1(), getY1());
	for (Line* childrenLine : *childrenLine) {
		childrenLine->updatePoint2();
	}
}

std::vector<Line*>* Line::createChildren(int nbChildren, float defaultAngle) {
	for (int i = 0; i < nbChildren; i++) {
		childrenLine->push_back(new Line(&x2, &y2, 0, (i*defaultAngle/(nbChildren-1))-(defaultAngle/2), getRank()+1, this));
	}
	return childrenLine;
}

void Line::draw(sf::RenderWindow* window) {
	graphicalLine.setFillColor(color);
	window->draw(graphicalLine);
	window->draw(graphicalNode);
	for (Line* childLine : *childrenLine) {
		childLine->draw(window);
	}
}