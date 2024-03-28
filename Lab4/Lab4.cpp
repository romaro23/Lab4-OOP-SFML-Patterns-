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
		break;
	case Keyboard::Key::Down:
		myFigure.move(0.0f, 30.0f, window);
		break;
	case Keyboard::Key::Right:
		myFigure.move(30.0f, 0.0f, window);
		break;
	case Keyboard::Key::Left:
		myFigure.move(-30.0f, 0.0f, window);
		break;
	case Keyboard::Key::R:
		caretaker.loadState();
		window.clear();
		for (auto figure : WindowWrapper::figures) {
			figure->draw(window);
		}
		window.display();
		break;
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
			it = find(figures.begin(), figures.end(), activeComposite);
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
			it = find(figures.begin(), figures.end(), activeComposite);
			if (it == figures.end()) {
				figures.push_back(activeComposite);
			}
		}
		else {
			cout << "Wrond answer. Try again" << endl;
		}
		WindowWrapper::figures = figures;
	}	
		break;
	case Keyboard::Key::C:
	{
		static FigurePrototype prototype;	
		prototype.repositoryState();
		cout << "From a repository or active figure? rep/act" << endl;
		string answer;
		cin >> answer;
		CompositeFigure* figure = nullptr;
		if (answer == "rep") {
			figure = prototype.cloneCompositeFromRepository();
		}
		else if (answer == "act") {
			prototype.createCompositePrototype(*dynamic_cast<CompositeFigure*>(&myFigure));
			figure = prototype.cloneComposite();
		}
		if (figure != nullptr) {
			figures.push_back(figure);
			WindowWrapper::figures = figures;
		}
	}	
		break;
	case Keyboard::Key::P:
	{
		static FigurePrototype prototype;	
		prototype.repositoryState();
		cout << "From a repository or active figure? rep/act" << endl;
		string answer;
		cin >> answer;
		Figure* figure = nullptr;
		if (answer == "rep") {
			figure = prototype.cloneFromRepository();
		}
		else if (answer == "act") {
			prototype.createPrototype(&myFigure);
			figure = prototype.clone();
		}
		if (figure != nullptr) {
			figures.push_back(figure);
			WindowWrapper::figures = figures;
		}		
	}	
		break;
	}
}
int main() {
	cout << "C - clone composite, S - save state, R - load state, P - clone figure, arrows - move, Num1 - create composite" << endl;
	RenderWindow& window = WindowWrapper::getWindow();
	RenderWindow& windowCopy = WindowWrapper::getWindow();
	cout << &window << endl;
	cout << &windowCopy << endl;
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
			else if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Key::Enter) {
					cout << "What figure you want to add? circle/square" << endl;
					string answer;
					cin >> answer;
					cout << "What color? 1 - red 2 - green 3 - blue" << endl;
					int colorAnswer;
					cin >> colorAnswer;
					Color color;
					if (answer == "circle") {
						switch (colorAnswer) {
						case 1:
							color = Color::Red;
							break;
						case 2:
							color = Color::Green;
							break;
						case 3:
							color = Color::Blue;
							break;
						default:
							color = Color::White;
							break;
						}
						figures.push_back(new Circle(50.0f, color));
						WindowWrapper::figures = figures;
					}
					else if (answer == "square") {
						switch (colorAnswer) {
						case 1:
							color = Color::Red;
							break;
						case 2:
							color = Color::Green;
							break;
						case 3:
							color = Color::Blue;
							break;
						default:
							color = Color::White;
							break;
						}
						figures.push_back(new Square(100.0f, color));
						WindowWrapper::figures = figures;
					}
					else {
						cout << "Wrong answer. Try again" << endl;
					}
				}
				if (active != nullptr) {
					handleKeyPress(event.key.code, *active, window);
				}		
				if (event.key.code == Keyboard::Key::Num1) {
					active = nullptr;
				}
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