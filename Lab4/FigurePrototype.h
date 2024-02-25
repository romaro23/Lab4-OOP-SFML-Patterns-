#pragma once
#include "Figure.h"
#include "CompositeFigure.h"
class FigurePrototype
{
private:
	Figure* figurePrototype;
	CompositeFigure* compositePrototype;
public:
	FigurePrototype(Figure* originalFigure) : figurePrototype(originalFigure) {}
	FigurePrototype(CompositeFigure* originalFigure) {
		compositePrototype = new CompositeFigure(originalFigure->cloneComposite());
	}
	Figure* clone() const {
		return figurePrototype->clone();
	}
	CompositeFigure* cloneComposite() const {
		return compositePrototype;
	}
};

