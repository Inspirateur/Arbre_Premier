#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Line {
public:
	Line(float* x, float* y, float length, float angle, int rank, Line* parentLine);
	inline int getX1() const { return int(*x1); }
	inline int getY1() const { return int(*y1); }
	inline int getX2() const { return int(x2); }
	inline int getY2() const { return int(y2); }
	inline int getLength() const { return int(l); }
	virtual inline float getAngle() const { return a+parentLine->getAngle(); }
	inline int getRank() const { return int(r); }
	inline Line* getParent() const { return parentLine; }
	inline std::vector<Line*>* getChildrenLines() const { return childrenLine; }
	inline sf::Color* getColor() { return &color; }
	void setL(float length);
	void setA(float angle);
	void addL(float length);
	std::vector<Line*>* createChildren(int nbChildren, float defaultAngle);
	void draw(sf::RenderWindow* window);
	void updatePoint2();

//for RootLine use
protected:
	Line(float length, float angle, int rank, Line* parent_Line);
	void setX1(float* x);
	void setY1(float* y);
	float a;

private:
	float* x1;
	float* y1;
	float x2;
	float y2;
	float l;
	int r;
	sf::Color color;
	Line* parentLine;
	std::vector<Line*>* childrenLine = new std::vector<Line*>;
	sf::RectangleShape graphicalLine;
	sf::CircleShape graphicalNode;
};