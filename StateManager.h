#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "State.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void handleEvent(sf::Event& e);
	void update();
	void draw(sf::RenderTarget& target);

	void addState(StateID id, State* state);
	void switchState(StateID id);
private:
	std::map<StateID, State*> states;
	StateID currentStateID;
	State* getCurrentState();
};

