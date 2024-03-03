#pragma once
#include "Memento.h"
#include "WindowWrapper.h"
#include <iostream>
class Caretaker
{
public:
	void saveState() {
		WindowWrapper::setMemento(memento);
		std::cout << "Saved" << std::endl;
	}
	void loadState() {
		WindowWrapper::getMemento(memento);
		std::cout << "Loaded" << std::endl;
	}
private:
	Memento memento;
};

