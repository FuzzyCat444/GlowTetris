#pragma once

#include <SFML/Graphics.hpp>

enum class Square
{
	Empty, Red, Yellow, Green, Cyan, Blue, Magenta, White
};

sf::Color squareColor(Square square);