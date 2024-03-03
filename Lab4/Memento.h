#pragma once
#include "Figure.h"
#include "Square.h"
#include "Circle.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
class Memento
{
	friend class WindowWrapper;	
	vector<Figure*> figures;
	void saveToFile() {
		ofstream output("figures.txt");
		if (!output) {
			cout << "Unable to open the file";	
		}
		for (const Figure* figure : figures) {
			figure->save(output);
		}
		output.close();
		figures.clear();
	}
	void loadFromFile() {
		figures.clear();
		ifstream input("figures.txt");
		if (!input) {
			cout << "Unable to open the file";
		}
		string line;
		while (getline(input, line)) {		
			char figureType = line[0];
			istringstream iss(line);
			Figure* tempFigure = nullptr;
			switch (figureType) {
			case 'S':
				tempFigure = new Square(0.0f, Color::White);
				break;
			case 'C':
				tempFigure = new Circle(0.0f, Color::White);
				break;
			}	
			tempFigure->load(iss);
			figures.push_back(tempFigure);
		}
		input.close();
	}
};

