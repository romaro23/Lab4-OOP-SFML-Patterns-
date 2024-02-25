#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class WindowWrapper
{
public:
	static RenderWindow& getWindow() {
		static RenderWindow window(VideoMode(800, 600), "SFML Window");
		return window;
	}
private:
	WindowWrapper() {}
};

