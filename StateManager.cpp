#include "StateManager.h"

StateManager::StateManager() : currentStateID{ -1 }
{
}

StateManager::~StateManager()
{
	for (auto it = states.begin(); it != states.end(); ++it)
	{
		delete it->second;
	}
}

void StateManager::handleEvent(sf::Event& e)
{
	State* current = getCurrentState();
	if (current != nullptr)
		current->handleEvent(e);
}

void StateManager::update()
{
	State* current = getCurrentState();
	if (current != nullptr)
		current->update();
}

void StateManager::draw(sf::RenderTarget& target)
{
	State* current = getCurrentState();
	if (current != nullptr)
		current->draw(target);
}

void StateManager::addState(StateID id, State* state)
{
	states.insert(std::pair<StateID, State*>(id, state));
}

void StateManager::switchState(StateID id)
{
	State* current = getCurrentState();
	if (current != nullptr)
		current->exit();
	currentStateID = id;
	current = getCurrentState();
	if (current != nullptr)
		current->enter();
}

State* StateManager::getCurrentState()
{
	auto it = states.find(currentStateID);
	if (it == states.end())
		return nullptr;
	return it->second;
}
