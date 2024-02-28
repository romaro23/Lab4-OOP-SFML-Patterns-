#pragma once
#include "Figure.h"
#include "CompositeFigure.h"
#include <iostream>
class FigurePrototype
{
private:
	Figure* figurePrototype;
	vector<Figure*> prototypes;
	vector<CompositeFigure*> compositePrototypes;
	CompositeFigure* compositePrototype;
public:
	FigurePrototype(Figure* originalFigure) {
		figurePrototype = originalFigure;
		prototypes.push_back(figurePrototype);
	}
	FigurePrototype(CompositeFigure* originalFigure) {
		compositePrototype = new CompositeFigure(originalFigure->cloneComposite());
		compositePrototypes.push_back(compositePrototype);
	}
	Figure* clone() const {
		return figurePrototype->clone();
	}
	CompositeFigure* cloneComposite() const {
		return compositePrototype;
	}
	Figure* cloneFromRepository() {
		if (!prototypes.empty()) {
			Figure* temp = prototypes.back()->clone();
			prototypes.pop_back();
			return temp;
		}
		else {
			std::cout << "The repository is empy!" << std::endl;
		}
		
	}
	CompositeFigure* cloneCompositeFromRepository() {
		if (!compositePrototypes.empty()) {
			CompositeFigure* temp = compositePrototypes.back();
			compositePrototypes.pop_back();
			return temp;
		}
		else {
			std::cout << "The repository is empy!" << std::endl;
		}
		
	}

};

