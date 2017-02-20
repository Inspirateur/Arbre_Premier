#include "Tree.h"
#include <iostream>
#include "RootLine.h"
#include "Line.h"

using namespace std;

Tree::Tree(vector<int>* _seed, int root_x, int root_y):
	seed(_seed),
	rootLine(new RootLine(root_x, root_y))
{
	//We create its children and add them to the growingLines
	vector<Line*>* tempChildren = rootLine->createChildren(seed->at(0), defaultAngle);
	for (Line* newGrowingLine : *tempChildren) {
		growingLines.push_back(newGrowingLine);
	}
}

//We seek the shared parent of line1 and line2 (they got one)
Line* Tree::getParentFrom2Node(Line* line1, Line* line2) const {
	//We first get to the same rank
	while (line1->getRank() < line2->getRank()) {
		line2 = line2->getParent();
	}
	while (line1->getRank() > line2->getRank()) {
		line1 = line1->getParent();
	}

	//Then we go down until we find the shared parent
	while (line1 != line2) {
		line1 = line1->getParent();
		line2 = line2->getParent();
	}

	//We return it
	return line1;
}

void Tree::update() {
	int i = 0;
	Line* growingLine;
	while(i < growingLines.size()) {
		growingLine = growingLines.at(i);
		growingLine->addL(growSpeed);
		//If the growing line is done
		if (growingLine->getLength() >= lineLen) {
			//We give it the wanted length
			growingLine->setL(lineLen);
			//If it's not a final line
			if (growingLine->getRank() < seed->size()) {
				//We create its children and add them to the growingLines
				vector<Line*>* tempChildren = growingLine->createChildren(seed->at(growingLine->getRank()), defaultAngle);
				for (Line* newGrowingLine : *tempChildren) {
					growingLines.push_back(newGrowingLine);
				}
			}
			//We remove it from growingLines vector
			growingLines.erase(find(growingLines.begin(), growingLines.end(), growingLine));
		} else {
			i++;
		}
	}
	//rootLine->setA(rootLine->getAngle() + 0.0005);
}

void Tree::draw(sf::RenderWindow* window) {
	rootLine->draw(window);
}