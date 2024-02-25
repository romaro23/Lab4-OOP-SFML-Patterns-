#pragma once
#include "MyColor.h"
#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
class Circle : public Figure
{
private:
    float radius;
    float startRadius;
    Color startColor;
    CircleShape circle;
    Vector2f position;
    Vector2f startPosition = this->position;
    std::vector<Vector2f> movementHistory;
public:
    Circle(float radius, Color color);
    FloatRect getGlobalBounds() override;
    void setTrailMovement(bool move) {
        trailMovement = move;
    }
    bool getTrailMovement() {
        return trailMovement;
    }
    void restore() override {
        circle.setFillColor(startColor);
        color = startColor;
        circle.setPosition(startPosition);
        position = startPosition;
        circle.setScale(Vector2f(0.9f, 0.9f));
    }
    Figure* clone() override {
        return new Circle(this->radius, this->color);
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

