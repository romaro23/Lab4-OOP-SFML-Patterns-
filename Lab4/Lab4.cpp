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
vector<Figure*> figures;
CompositeFigure* activeComposite = nullptr;
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
	/*case Keyboard::Key::R:
		figure.decompose();
		caretaker.loadState();
		figure.combine(WindowWrapper::figures[2]);
		window.clear();
		for (auto figure : WindowWrapper::figures) {
			figure->draw(window);
		}
		window.display();
		cout << "R" << endl;
		break;*/
	case Keyboard::Key::S:
		caretaker.saveState();
		break;
	case Keyboard::Key::Num1:
	{
		cout << "Add to and old or create a new composite? old/new" << endl;
		string answer;
		cin >> answer;		
		static CompositeFigure oldComposite;
		if (answer == "old") {
			if (activeComposite == nullptr) {
				activeComposite = &oldComposite;
			}
			auto it = find(figures.begin(), figures.end(), &myFigure);
			figures.erase(it);
			activeComposite->combine(&myFigure);
			//Change myFigure to activeComposite
			it = find(figures.begin(), figures.end(), &myFigure);
			if (it == figures.end()) {
				figures.push_back(activeComposite);
			}		
		}
		else if (answer == "new") {
			auto it = find(figures.begin(), figures.end(), &myFigure);
			figures.erase(it);
			static CompositeFigure newComposite;
			activeComposite = &newComposite;
			activeComposite->combine(&myFigure);
			it = find(figures.begin(), figures.end(), &myFigure);
			if (it != figures.end()) {
				figures.push_back(activeComposite);
			}
			
		}	
		WindowWrapper::figures = figures;
	}	
		break;
	case Keyboard::Key::C:
	{
		FigurePrototype prototype;
		prototype.createCompositePrototype(*dynamic_cast<CompositeFigure*>(&myFigure));
		CompositeFigure* figure = prototype.cloneComposite();
		figures.push_back(figure);
		WindowWrapper::figures = figures;
	}	
		break;
	case Keyboard::Key::P:
	{
		FigurePrototype prototype;
		prototype.createPrototype(&myFigure);
		Figure* figure = prototype.clone();
		figures.push_back(figure);
		WindowWrapper::figures = figures;
	}	
		break;
	}
}
int main() {
	cout << "R - restore, C - clone composite, S - save state, P - clone figure, arrows - move, Num1 - create composite" << endl;
	RenderWindow& window = WindowWrapper::getWindow();
	Figure* figure1 = new Square(100.0f, Color::Green);
	Figure* figure2 = new Circle(50.0f, Color::Blue);

	figures.push_back(figure1);
	figures.push_back(figure2);

	Figure* active = nullptr;
	WindowWrapper::figures = figures;
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