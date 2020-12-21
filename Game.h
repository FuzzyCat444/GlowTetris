#pragma once
#include <SFML/Graphics.hpp>

#include "StateManager.h"

class Game
{
public:
	Game();
	void start();

	static constexpr StateID playStateID = 0;
private:
	StateManager stateManager;
};

