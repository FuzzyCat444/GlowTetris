#include "Square.h"

sf::Color squareColor(Square square)
{
	switch (square)
	{
	case Square::Empty:
		return sf::Color::Black;
	case Square::Red:
		return sf::Color::Red;
	case Square::Yellow:
		return sf::Color::Yellow;
	case Square::Green:
		return sf::Color::Green;
	case Square::Cyan:
		return sf::Color::Cyan;
	case Square::Blue:
		return sf::Color::Blue;
	case Square::Magenta:
		return sf::Color::Magenta;
	case Square::White:
		return sf::Color::White;
	}
}
