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
    CircleShape circle;
    Vector2f position;
    std::vector<Vector2f> movementHistory;
public:
    Circle(float radius, Color color);
    FloatRect getGlobalBounds() override;
    void move(float x, float y, RenderWindow& window) override;

    void draw(RenderWindow& window, bool withTrail) override;

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

