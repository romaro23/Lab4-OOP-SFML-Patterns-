#include "WindowWrapper.h"
RenderWindow& WindowWrapper::getWindow() {
		static RenderWindow window(VideoMode(800, 600), "SFML Window");
		return window;
}
vector<Figure*> WindowWrapper::figures;
