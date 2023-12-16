#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "MyColor.h"
#include <iostream>
using namespace sf;
using namespace std;

void handleKeyPress(Keyboard::Key key, Figure& myFigure, RenderWindow& window) {
	switch (key) {
	case Keyboard::Key::Up:
		myFigure.move(0.0f, -10.0f, window);
		cout << "Up" << endl;
		break;
	case Keyboard::Key::Down:
		myFigure.move(0.0f, 10.0f, window);
		cout << "Down" << endl;
		break;
	case Keyboard::Key::Right:
		myFigure.move(10.0f, 0.0f, window);
		cout << "Right" << endl;
		break;
	case Keyboard::Key::Left:
		myFigure.move(-10.0f, 0.0f, window);
		cout << "Left" << endl;
		break;
	case Keyboard::Key::Enter:
		cout << "Enter" << endl;
		myFigure.autoMove(window);
		break;
	case Keyboard::Key::H:
		myFigure.hide();
		cout << "H" << endl;
		break;
	case Keyboard::Key::S:
		myFigure.show();
		cout << "S" << endl;
		break;
	case Keyboard::Key::C:
		MyColor color;
		cout << "Choose color" << endl;
		cout << "1. Red" << endl;
		cout << "2. Blue" << endl;
		cout << "3. Green" << endl;
		cout << "4. Yellow" << endl;
		int option;
		cin >> option;
		switch (option) {
		case 1:
			color = MyColor::Red;
			break;
		case 2:
			color = MyColor::Blue;
			break;
		case 3:
			color = MyColor::Green;
			break;
		case 4:
			color = MyColor::Yellow;
			break;
		default:
			color = MyColor::White;
			break;
		}
		myFigure.setColor(color);
		break;
	}
}
int main() {
	Figure* figures[3];
	Figure* active;
	figures[0] = new Circle(50.0f, Color::Blue);
	figures[1] = new Square(100.0f, Color::Green);
	figures[2] = new Circle(50.0f, Color::Yellow);
	RenderWindow window(VideoMode(800, 600), "SFML Window");
	active = figures[0];
	figures[0]->move(100.0f, 100.0f, window);
	figures[1]->move(100.0f, 200.0f, window);
	figures[2]->move(100.0f, 300.0f, window);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					for (auto figure : figures) {
						
						Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
						std::cout << "Global Bounds: " << figure->getGlobalBounds().left << ", " << figure->getGlobalBounds().top << std::endl;
						std::cout << "Mouse Position: " << mousePosition.x << ", " << mousePosition.y << std::endl;

						if (figure->getGlobalBounds().contains(mousePosition)) {
							active = figure;
						}
						figure->draw(window, true);

					}

				}
			}
			else if (event.type == Event::KeyPressed) {
				handleKeyPress(event.key.code, *active, window);
			}
		}

		window.clear();

		for (auto figure : figures) {
			figure->draw(window, true);
		}

		window.display();
	}

}