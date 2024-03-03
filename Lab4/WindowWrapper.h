#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Figure.h"
#include "Memento.h"
using namespace sf;
using namespace std;
class WindowWrapper
{
public:
	static vector<Figure*> figures;
	static RenderWindow& getWindow();
	static void setMemento(Memento& memento) {	
		memento.figures = figures;
		memento.saveToFile();
	}
	static void getMemento(Memento& memento) {
		memento.loadFromFile();
		figures = memento.figures;
	}
private:
	WindowWrapper() {}

};

