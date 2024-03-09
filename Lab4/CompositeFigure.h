#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyColor.h"
#include <algorithm>
#include <sstream>
using namespace sf;
using namespace std;
class CompositeFigure: public Figure
{
public:
	vector<Figure*> compositeFigure;
	CompositeFigure(vector<Figure*> composite) {
		compositeFigure = composite;
	}
	CompositeFigure() {}
	~CompositeFigure() {
		compositeFigure.clear();
	}
	std::ostream& save(std::ostream& os) const override {
		os << '{' << endl;
		for (auto figure : compositeFigure) {
			figure->save(os);
		}
		os << '}' << endl;
		return os;
	}

	std::istream& load(std::istream& is) override {
		for (auto figure : compositeFigure) {
			figure->load(is);
		}
		return is;
	}
	string toString() {
		stringstream ss;
		ss << "Composite { ";
		for (auto figure : compositeFigure) {
			ss << figure->toString();
		}
		ss << " } ";
		return ss.str();
	}
	bool isBelongs(Figure* figure) {
		if (count(compositeFigure.begin(), compositeFigure.end(), figure)) {
			return true;
		}
		return false;
	}
	void decompose() {
		for (auto figure : compositeFigure) {
			compositeFigure.pop_back();
		}
	}
	void combine(Figure* figure) {
		if (!isBelongs(figure)) {
			compositeFigure.push_back(figure);
		}	
	}
	void combine(CompositeFigure figure) {
		if (!isBelongs(&figure)) {
			compositeFigure.push_back(&figure);
		}
	}
	void draw(RenderWindow& window) {
		if (!compositeFigure.empty()) {
			for (auto figure : compositeFigure) {
				figure->draw(window);
			}
		}	
	}
	void move(float x, float y, RenderWindow& window) {
		for (auto figure : compositeFigure) {
			figure->move(x, y, window);
		}
	}
	void show() {
		for (auto figure : compositeFigure) {
			figure->show();
		}
	}
	void hide() {
		for (auto figure : compositeFigure) {
			figure->hide();
		}
	}
	FloatRect getGlobalBounds() {
		FloatRect bounds = compositeFigure[0]->getGlobalBounds();
		for (size_t i = 1; i < compositeFigure.size(); ++i) {
			const FloatRect& figureBounds = compositeFigure[i]->getGlobalBounds();
			bounds.left = std::min(bounds.left, figureBounds.left);
			bounds.top = std::min(bounds.top, figureBounds.top);
			bounds.width = std::max(bounds.left + bounds.width, figureBounds.left + figureBounds.width) - bounds.left;
			bounds.height = std::max(bounds.top + bounds.height, figureBounds.top + figureBounds.height) - bounds.top;
		}
		return bounds;
		
	}
	void autoMove(RenderWindow& window) {
		for (auto figure : compositeFigure) {
			figure->autoMove(window);
		}
	}
	void setColor(MyColor color) {
		for (auto figure : compositeFigure) {
			figure->setColor(color);
		}
	}
	void setTrailMovement(bool move) {
		for (auto figure : compositeFigure) {
			figure->setTrailMovement(move);
		}
	}
	bool getTrailMovement() {
		for (auto figure : compositeFigure) {
			return figure->getTrailMovement();
		}
	}
	void restore() {
		for (auto figure : compositeFigure) {
			figure->restore();
		}
		decompose();
	}
	void setScale(float x, float y) {
		for (auto figure : compositeFigure) {
			figure->setScale(x, y);
		}
	}
	Vector2f getPosition() {
		for (auto figure : compositeFigure) {
			return figure->getPosition();
		}
	}
	void setOutline(float thickness, Color color)  {
	}
	bool checkIntersection(Figure* figure)  {
		return true;
	}
	bool updateWindowCollision(RenderWindow& window) {
		return true;
	}
	vector<Figure*> cloneComposite() {
		vector<Figure*> copy;
		for (auto figure : compositeFigure) {
			copy.push_back(figure->clone());
		}
		return copy;
	}
	Figure* clone() {
		vector<Figure*> copy;
		for (auto figure : compositeFigure) {
			copy.push_back(figure->clone());
		}
		return new CompositeFigure(copy);
	}
};

