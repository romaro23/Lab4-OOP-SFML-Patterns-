#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyColor.h"
#include <algorithm>
using namespace sf;
using namespace std;
class CompositeFigure: public Figure
{
private:
	vector<Figure*> compositeFigure;
public:
	CompositeFigure(vector<Figure*> composite) {
		compositeFigure = composite;
	}
	CompositeFigure() {}
	~CompositeFigure() {
		compositeFigure.clear();
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
	void draw(RenderWindow& window) {
		for (auto figure : compositeFigure) {
			figure->draw(window);
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
		for (auto figure : compositeFigure) {
			return figure->getGlobalBounds();
		}
		
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
		return compositeFigure[0];
	}
};
