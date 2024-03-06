#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Square.h"
#include "CompositeFigure.h"
#include "WindowWrapper.h"
#include "FigurePrototype.h"
#include "MyColor.h"
#include "Caretaker.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace sf;
using namespace std;
Caretaker caretaker;
CompositeFigure figure;
vector<Figure*> figures;
void handleKeyPress(Keyboard::Key key, Figure& myFigure, RenderWindow& window) {
	switch (key) {
	case Keyboard::Key::Up:
		myFigure.move(0.0f, -30.0f, window);
		cout << "Up" << endl;
		break;
	case Keyboard::Key::Down:
		myFigure.move(0.0f, 30.0f, window);
		cout << "Down" << endl;
		break;
	case Keyboard::Key::Right:
		myFigure.move(30.0f, 0.0f, window);
		cout << "Right" << endl;
		break;
	case Keyboard::Key::Left:
		myFigure.move(-30.0f, 0.0f, window);
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
	case Keyboard::Key::R:
		figure.decompose();
		caretaker.loadState();
		figure.combine(WindowWrapper::figures[2]);
		window.clear();
		for (auto figure : WindowWrapper::figures) {
			figure->draw(window);
		}
		window.display();
		cout << "R" << endl;
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
	case Keyboard::Key::P:
		FigurePrototype prototype(&myFigure);
		Figure* figure3 = prototype.cloneFromRepository();
		figures.push_back(figure3);
		WindowWrapper::figures = figures;
		break;
	}
}
int main() {
	cout << "R - restore, C - color, S - show, H - hide, Enter - start auto move, RShift - stop, arrows - move" << endl;
	RenderWindow& window = WindowWrapper::getWindow();
	Figure* figure1 = new Square(100.0f, Color::Green);
	Figure* figure2 = new Circle(50.0f, Color::Blue);
	figure.combine(new Square(120.0f, Color::Yellow));	
	figure.move(100.0f, 100.0f, window);
	figures.push_back(figure1);
	figures.push_back(figure2);
	figures.push_back(&figure);
	Figure* active = nullptr;
	WindowWrapper::figures = figures;
	caretaker.saveState();
	while (window.isOpen()) {		
		Event event;
		while (window.pollEvent(event)) {			
			if (event.type == Event::Closed) {
				for (int i = 0; i < figures.size(); i++) {
					figures.pop_back();
				}
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
					for (auto figure : figures) {
						if (figure->getGlobalBounds().contains(mousePosition)) {
							active = figure;
						}
					}
					
				}
			}
			else if (event.type == Event::KeyPressed && active != nullptr) {
				if (event.key.code == Keyboard::Key::LShift) {
					active->move(figure.getPosition().x, figure.getPosition().y, window);
					figure.combine(active);
					auto it = find(figures.begin(), figures.end(), active);
					figures.erase(it);
					figures.push_back(&figure);
					WindowWrapper::figures = figures;
					active = nullptr;
				}
				handleKeyPress(event.key.code, *active, window);			
			}			
		}
		sleep(milliseconds(100));
		window.clear();
		figures = WindowWrapper::figures;
		for (auto figure : WindowWrapper::figures) {
			figure->draw(window);
		}
		window.display();
	}

}