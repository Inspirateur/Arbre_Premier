#pragma once
#include <vector>
#include "Line.h"

class Tree {
public:
	Tree(std::vector<int>* _seed, int root_x, int root_y);
	Line* getParentFrom2Node(Line* line1, Line* line2) const;
	void update();
	void draw(sf::RenderWindow* window);

private:
	std::vector<int>* seed;
	std::vector<Line*> growingLines;
	Line* rootLine;
	float growSpeed = 0.5;
	float lineLen = 50.0;
	float defaultAngle = 0.8;
	bool collision = false;
};