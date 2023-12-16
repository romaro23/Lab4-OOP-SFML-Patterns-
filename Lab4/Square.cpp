#include "Square.h"
#include <iostream>
#include "MyColor.h"
#include <SFML/Graphics.hpp>
using namespace sf;
Square::Square(float side, Color color) {
    trailMovement = false;
    this->side = side;
    square = RectangleShape(Vector2f(side, side));
    this->color = color;
    square.setFillColor(color);
}

void Square::move(float x, float y, RenderWindow& window) {
    Vector2f movement(x, y);
    position += movement;
        
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
    movementHistory.push_back(position);
}
FloatRect Square::getGlobalBounds() {
    return square.getGlobalBounds();
}
void Square::draw(RenderWindow& window, bool withTrail) {
    window.draw(square);
    if (withTrail) {
        for (const auto& position : movementHistory) {
            RectangleShape trailSquare;
            trailSquare.setSize(Vector2f(side, side));
            trailSquare.setFillColor(this->color);
            trailSquare.setPosition(position);
            window.draw(trailSquare);
        }
    }
    
}
void Square::setScale(float x, float y) {

}
Vector2f Square::getPosition() {
    return square.getTransform().transformPoint(square.getPosition());
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
            movementHistory.push_back(position);
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
        square.setFillColor(Color::Red);
        break;
    case Blue:
        square.setFillColor(Color::Blue);
        break;
    case Green:
        square.setFillColor(Color::Green);
        break;
    case Yellow:
        square.setFillColor(Color::Yellow);
        break;
    case White:
        square.setFillColor(Color::White);
        break;
    }
}