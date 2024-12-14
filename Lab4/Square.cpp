#include "Square.h"
#include <iostream>
#include "MyColor.h"
#include <SFML/Graphics.hpp>
using namespace sf;
Square::Square(float side, Color color) {
    trailMovement = false;
    this->side = side;
    startSide = side;
    square = RectangleShape(Vector2f(side, side));
    this->color = color;
    square.setFillColor(color);
    startColor = color;
}

void Square::move(float x, float y, RenderWindow& window) {
    Vector2f movement(x, y);
    position += movement;
    movementHistory.push_back(position);
    if (square.getPosition().x > window.getSize().x) {
        position.x = 0;
    }
    if (square.getPosition().x < 0) {
        position.x = window.getSize().x;
    }
    if (square.getPosition().y < 0) {
        position.y = window.getSize().y;
    }
    if (square.getPosition().y > window.getSize().y) {
        position.y = 0;
    }
    
    square.setPosition(position);
    if (this->getTrailMovement()) {
        for (auto position_ : movementHistory) {
            RectangleShape trailSquare;
            trailSquare.setSize(Vector2f(side, side));
            trailSquare.setFillColor(this->color);
            trailSquare.setPosition(position_);
            window.draw(trailSquare);
            window.display();
        }       
    }
    
}
void Square::setPosition(float x, float y) {
    Vector2f movement(x, y);
    position += movement;
    square.setPosition(position);
}
FloatRect Square::getGlobalBounds() {
    return square.getGlobalBounds();
}
void Square::draw(RenderWindow& window) {
    window.draw(square);
}
void Square::setScale(float x, float y) {
    square.setScale(x, y);
}
Vector2f Square::getPosition() {
    return square.getPosition();
}
bool Square::updateWindowCollision(RenderWindow& window) {
    return true;
}
void Square::show() {
    square.setFillColor(this->color);
}
void Square::hide() {
    square.setFillColor(Color::Transparent);
}
void Square::autoMove(RenderWindow& window) {
    float radius = 10.0f;
    float angle = 0.0f;
    Event event;
    while (window.pollEvent(event)) {
        while (event.key.code != Keyboard::Key::RShift) {
            if (square.getPosition().x > window.getSize().x) {
                position.x = 0;
            }
            if (square.getPosition().x < 0) {
                position.x = window.getSize().x;
            }
            if (square.getPosition().y < 0) {
                position.y = window.getSize().y;
            }
            if (square.getPosition().y > window.getSize().y) {
                position.y = 0;
            }
            float currentX = position.x;
            float currentY = position.y;
            position.x = currentX + radius * std::cos(angle * (3.14159 / 180.0));
            position.y = currentY + radius * std::sin(angle * (3.14159 / 180.0));
            square.setPosition(position);
            window.clear();
            window.draw(square);
            window.display();
            sleep(milliseconds(100));
            angle += 5.0f;
            window.pollEvent(event);
        }
        std::cout << "RShift" << std::endl;
    }
}
void Square::setColor(MyColor color) {
    switch (color) {
    case Red:
        this->color = Color::Red;
        square.setFillColor(Color::Red);
        break;
    case Blue:
        this->color = Color::Blue;
        square.setFillColor(Color::Blue);
        break;
    case Green:
        this->color = Color::Green;
        square.setFillColor(Color::Green);
        break;
    case Yellow:
        this->color = Color::Yellow;
        square.setFillColor(Color::Yellow);
        break;
    case White:
        this->color = Color::White;
        square.setFillColor(Color::White);
        break;
    }
}