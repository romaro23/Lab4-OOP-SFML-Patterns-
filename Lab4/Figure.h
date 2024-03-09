#pragma once
#include <SFML/Graphics.hpp>
#include "MyColor.h"
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;
class Figure
{
public:
	Color color;
	bool trailMovement;
	virtual std::ostream& save(std::ostream& os) const = 0;
	virtual std::istream& load(std::istream& is) = 0;
	virtual void setTrailMovement(bool move) = 0;
	virtual bool getTrailMovement() = 0;
	virtual void restore() = 0;
	virtual FloatRect getGlobalBounds() = 0;
	virtual void setScale(float x, float y) = 0;
	virtual Vector2f getPosition() = 0;
	virtual bool checkIntersection(Figure* figure) = 0;
	virtual bool updateWindowCollision(RenderWindow& window) = 0;
	virtual void autoMove(RenderWindow& window) = 0;
	virtual void hide() = 0;
	virtual void show() = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual void move(float x, float y, RenderWindow& window) = 0;
	virtual void setOutline(float thickness, Color color) = 0;
	virtual void setColor(MyColor color) = 0;
	virtual Figure* clone() = 0;
	virtual string toString() = 0;
};

