#pragma once
#include "MyColor.h"
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace sf;
using namespace std;
class Square : public Figure
{
private:
    float side;
    float startSide;
    Color startColor;
    RectangleShape square;
    Vector2f position;
    Vector2f startPosition;
    std::vector<Vector2f> movementHistory;
public:
    Square(float side, Color color);
    FloatRect getGlobalBounds() override;
    void setTrailMovement(bool move) override {
        trailMovement = move;
    }
    bool getTrailMovement() override {
        return trailMovement;
    }
    std::ostream& save(std::ostream& os) const override {
        os << "S" << " " << this->position.x << " " << this->position.y << " " << this->color.toInteger() << " " << this->side << endl;
        return os;
    }

    std::istream& load(std::istream& is) override {
        char type;
        int x, y, side;
        long long color;
        is >> type >> x >> y >> color >> side;
        this->position.x = x; 
        this->position.y = y;
        this->square.setPosition(x, y);
        this->color = Color(color);
        this->square.setFillColor(Color(color));
        this->side = side;
        this->square.setSize(Vector2f(side, side));
        return is;
    }
    string toString() {
        stringstream ss;
        ss << "Square " << "R: " << static_cast<int>(this->color.r) << " G: " << static_cast<int>(this->color.g) << " B: " << static_cast<int>(this->color.b) << " ";
        return ss.str();
    }
    void restore() override {
        square.setFillColor(startColor);
        color = startColor;
        square.setPosition(startPosition);
        position = startPosition;
        square.setScale(Vector2f(1.2f, 1.2f));
    }
    Figure* clone() override {
        Square* square = new Square(this->side, this->color);
        square->position = this->square.getPosition();
        square->square.setPosition(this->square.getPosition());
        return square;
    }
    void move(float x, float y, RenderWindow& window) override;

    void draw(RenderWindow& window) override;

    void setScale(float x, float y) override;

    Vector2f getPosition() override;

    bool checkIntersection(Figure* figure) override {
        return true;
    }

    bool updateWindowCollision(RenderWindow& window) override;

    void autoMove(RenderWindow& window) override;

    void hide() override;

    void show() override;

    void setOutline(float thickness, Color color) override {
    }

    void setColor(MyColor color) override;
};

