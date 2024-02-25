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
	vector<Figure*> CompositeFigure;
public:
	~CompositeFigure() {
		CompositeFigure.clear();
	}
	bool isBelongs(Figure* figure) {
		if (count(CompositeFigure.begin(), CompositeFigure.end(), figure)) {
			return true;
		}
		return false;
	}
	void decompose() {
		for (auto figure : CompositeFigure) {
			CompositeFigure.pop_back();
		}
	}
	void combine(Figure* figure) {
		if (!isBelongs(figure)) {
			CompositeFigure.push_back(figure);
		}	
	}
	void draw(RenderWindow& window) {
		for (auto figure : CompositeFigure) {
			figure->draw(window);
		}
	}
	void move(float x, float y, RenderWindow& window) {
		for (auto figure : CompositeFigure) {
			figure->move(x, y, window);
		}
	}
	void show() {
		for (auto figure : CompositeFigure) {
			figure->show();
		}
	}
	void hide() {
		for (auto figure : CompositeFigure) {
			figure->hide();
		}
	}
	FloatRect getGlobalBounds() {
		for (auto figure : CompositeFigure) {
			return figure->getGlobalBounds();
		}
		
	}
	void autoMove(RenderWindow& window) {
		for (auto figure : CompositeFigure) {
			figure->autoMove(window);
		}
	}
	void setColor(MyColor color) {
		for (auto figure : CompositeFigure) {
			figure->setColor(color);
		}
	}
	void setTrailMovement(bool move) {
		for (auto figure : CompositeFigure) {
			figure->setTrailMovement(move);
		}
	}
	bool getTrailMovement() {
		for (auto figure : CompositeFigure) {
			return figure->getTrailMovement();
		}
	}
	void restore() {
		for (auto figure : CompositeFigure) {
			figure->restore();
		}
		decompose();
	}
	void setScale(float x, float y) {
		for (auto figure : CompositeFigure) {
			figure->setScale(x, y);
		}
	}
	Vector2f getPosition() {
		for (auto figure : CompositeFigure) {
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
};

