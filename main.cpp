#include <ctime>
#include <cstdlib>

#include "Game.h"

int main(int argc, char** argv) 
{
	std::srand(std::time(nullptr));
	Game game;
	game.start();
	return 0;
}