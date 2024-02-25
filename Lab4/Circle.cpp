#include "Circle.h"
#include <iostream>
#include "MyColor.h"
#include <SFML/Graphics.hpp>
using namespace sf;
Circle::Circle(float radius, Color color) {
    trailMovement = false;
    this->radius = radius;
    startRadius = radius;
    circle = CircleShape(radius);
    this->color = color;
    circle.setFillColor(color);
    startColor = color;
}
FloatRect Circle::getGlobalBounds() {
    return circle.getGlobalBounds();
}

void Circle::move(float x, float y, RenderWindow& window) {
    Vector2f movement(x, y);
    position += movement;
    movementHistory.push_back(position);
    if (circle.getPosition().x > window.getSize().x) {
        position.x = 0;
    }
    if (circle.getPosition().x < 0) {
        position.x = window.getSize().x;
    }
    if (circle.getPosition().y < 0) {
        position.y = window.getSize().y;
    }
    if (circle.getPosition().y > window.getSize().y) {
        position.y = 0;
    }
    circle.setPosition(position); 
    if (this->getTrailMovement()) {
        for (auto position_ : movementHistory) {
            CircleShape trailCircle;
            trailCircle.setRadius(radius);
            trailCircle.setFillColor(this->color);
            trailCircle.setPosition(position_);
            window.draw(trailCircle);
            window.display();
        }
        
    }
}
void Circle::draw(RenderWindow& window) {
    window.draw(circle);
}
void Circle::setScale(float x, float y) {
    circle.setScale(x, y);
}
Vector2f Circle::getPosition() {
    return circle.getPosition();
}
bool Circle::updateWindowCollision(RenderWindow& window) {
    return true;
}
void Circle::show() {
    circle.setFillColor(this->color);
}
void Circle::hide() {
    circle.setFillColor(Color::Transparent);
}
void Circle::autoMove(RenderWindow& window) {
    float radius = 10.0f;
    float angle = 0.0f;
    Event event;
    while (window.pollEvent(event)) {
        while (event.key.code != Keyboard::Key::RShift) {
            if (circle.getPosition().x > window.getSize().x) {
                position.x = 0;
            }
            if (circle.getPosition().x < 0) {
                position.x = window.getSize().x;
            }
            if (circle.getPosition().y < 0) {
                position.y = window.getSize().y;
            }
            if (circle.getPosition().y > window.getSize().y) {
                position.y = 0;
            }
            float currentX = position.x;
            float currentY = position.y;
            position.x = currentX + radius * std::cos(angle * (3.14159 / 180.0));
            position.y = currentY + radius * std::sin(angle * (3.14159 / 180.0));
            circle.setPosition(position);
            window.clear();
            window.draw(circle);
            window.display();
            sleep(milliseconds(100));
            angle += 5.0f;
            window.pollEvent(event);
        }
        std::cout << "RShift" << std::endl;
    }
    
}
void Circle::setColor(MyColor color) {
    switch (color) {
    case Red:
        this->color = Color::Red;
        circle.setFillColor(Color::Red);
        break;
    case Blue:
        this->color = Color::Blue;
        circle.setFillColor(Color::Blue);
        break;
    case Green:
        this->color = Color::Green;
        circle.setFillColor(Color::Green);
        break;
    case Yellow:
        this->color = Color::Yellow;
        circle.setFillColor(Color::Yellow);
        break;
    case White:
        this->color = Color::White;
        circle.setFillColor(Color::White);
        break;
    }
}