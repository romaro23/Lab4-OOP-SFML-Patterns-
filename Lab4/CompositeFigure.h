#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyColor.h"
#include <algorithm>
#include <sstream>
#include "Iterator.h"
using namespace sf;
using namespace std;
class CompositeFigure: public Figure
{
	friend class Iterator<Figure*>;
public:
	vector<Figure*> compositeFigure;
	CompositeFigure(vector<Figure*> composite) {
		compositeFigure = composite;
	}
	CompositeFigure() {}
	~CompositeFigure() {
		compositeFigure.clear();
	}
	void setPosition(float x, float y) override {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->setPosition(x, y);
		}
	}
	Iterator<Figure*>* createIterator() {
		return new Iterator<Figure*>(compositeFigure);
	}
	ostream& save(std::ostream& os) const override {
		os << '{' << endl;
		for (auto figure : compositeFigure) {
			figure->save(os);
		}
		os << '}' << endl;
		return os;
	}

	istream& load(std::istream& is) override {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->load(is);
		}
		return is;
	}
	string toString() {
		stringstream ss;
		ss << "Composite { ";
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			ss << it->current()->toString();
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
			Iterator<Figure*>* it = createIterator();
			for (it->first(); !it->isDone(); it->next()) {
				it->current()->draw(window);
			}
		}	
	}
	void move(float x, float y, RenderWindow& window) {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->move(x, y, window);
		}
	}
	void show() {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->show();
		}
	}
	void hide() {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->hide();
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
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->autoMove(window);
		}
	}
	void setColor(MyColor color) {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->setColor(color);
		}
	}
	void setTrailMovement(bool move) {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->setTrailMovement(move);
		}
	}
	bool getTrailMovement() {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			return it->current()->getTrailMovement();
		}
	}
	void restore() {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->restore();
		}
		decompose();
	}
	void setScale(float x, float y) {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			it->current()->setScale(x, y);
		}
	}
	Vector2f getPosition() {
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			return it->current()->getPosition();
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
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			copy.push_back(it->current()->clone());
		}
		return copy;
	}
	Figure* clone() {
		vector<Figure*> copy;
		Iterator<Figure*>* it = createIterator();
		for (it->first(); !it->isDone(); it->next()) {
			copy.push_back(it->current()->clone());
		}
		return new CompositeFigure(copy);
	}
};

