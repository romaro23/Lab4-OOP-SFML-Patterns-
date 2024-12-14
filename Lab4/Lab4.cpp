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
#include <thread>
#include <chrono>
#include <time.h>

using namespace sf;
using namespace std;
Caretaker caretaker;
vector<Figure*> figures;
bool removed = true;
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
int getRandom(int min, int max) {
	
	return rand() % (max - min + 1) + min;
}
Color getRandomColor() {
	int random = getRandom(1, 5);
	switch (random) {
	case 1:
		return Color::White;
	case 2:
		return Color::Green;
	case 3:
		return Color::Yellow;
	case 4:
		return Color::Blue;
	case 5:
		return Color::Red;
	}
}
void removeFigureThread(Figure* figure, Figure* target) {
	removed = false;
	figures.erase(remove_if(figures.begin(), figures.end(), [&](Figure* f) {
		return f == figure || f == target;
		}), figures.end());
	WindowWrapper::figures = figures;
	removed = true;
}
void checkTargetThread() {
	while (true) {
		if (figures.size() > 1 && removed) {
			int random = getRandom(0, figures.size() - 1);
			for (auto figure : WindowWrapper::figures) {
				if (find(figures.begin(), figures.end(), figure->target) == figures.end()) {
					figure->haveTarget = false;
				}
				if (!figure->haveTarget) {
					figure->target = figures[random];
					while (figure == figure->target) {
						random = getRandom(0, figures.size() - 1);
						figure->target = figures[random];
					}
					figure->target->isTarget = true;
					figure->haveTarget = true;
				}
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
		
	}
	
}
void moveFigureThread(RenderWindow* window) {
	
	while (true) {
		if (figures.size() > 1 && removed) {
			Vector2f position;
			Vector2f targetPosition;
			float stepX;
			float stepY;
			for (int i = 0; i < figures.size(); i++) {
				Figure* figure = figures[i];
				position = figure->getPosition();
				if (figures.size() > 1 && figure->haveTarget == true) {
					while (!figure->getGlobalBounds().intersects(figure->target->getGlobalBounds())) {
						targetPosition = figure->target->getPosition();
						stepX = (targetPosition.x - position.x) / 7;
						stepY = (targetPosition.y - position.y) / 7;
						figure->move(stepX, stepY, *window);
						this_thread::sleep_for(chrono::milliseconds(1000));
					}
					thread(removeFigureThread, figure, figure->target).detach();
				}
			}
		}
	}		
}
void addFiguresThread(RenderWindow* window) {
	
	while (figures.size() < 10) {		
		float x = getRandom(0, 500);
		float y = getRandom(0, 500);
		this_thread::sleep_for(chrono::milliseconds(1000));
		Figure* figure = nullptr;
		int random = getRandom(1, 2);
		switch (random) {
		case 1:
			figure = new Square(100.0f, getRandomColor());
			break;
		case 2:
			figure = new Circle(50.0f, getRandomColor());
			break;
		}
		figure->move(x, y, *window);
		figures.push_back(figure);
		WindowWrapper::figures = figures;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}	
}


int main() {
	srand((time(NULL)));
	cout << "C - clone composite, S - save state, R - load state, P - clone figure, arrows - move, Num1 - create composite" << endl;
	
	RenderWindow& window = WindowWrapper::getWindow();
	RenderWindow& windowCopy = WindowWrapper::getWindow();
	cout << &window << endl;
	cout << &windowCopy << endl;
	thread addThread([&]() { addFiguresThread(&window); });
	thread checkThread(checkTargetThread);
	thread moveThread([&]() { moveFigureThread(&window); });
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
	addThread.join();
	checkThread.join();
	moveThread.join();
}