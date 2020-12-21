#pragma once

#include <SFML/Graphics.hpp>

typedef int StateID;

class State
{
public:
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void handleEvent(sf::Event& e) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
};

