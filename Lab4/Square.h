#pragma once
#include "MyColor.h"
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
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
    void restore() override {
        square.setFillColor(startColor);
        color = startColor;
        square.setPosition(startPosition);
        position = startPosition;
        square.setScale(Vector2f(1.2f, 1.2f));
    }
    Figure* clone() override {
        return new Square(this->side, this->color);
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

