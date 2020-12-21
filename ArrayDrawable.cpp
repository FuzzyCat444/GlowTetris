#include "ArrayDrawable.h"

ArrayDrawable::ArrayDrawable() : columns{ 0 }, rows{ 0 }, offsetX{ 0.0f }, offsetY{ 0.0f }, drawables{ nullptr }
{
}

void ArrayDrawable::setDimensions(int columns, int rows, float offsetX, float offsetY)
{
	this->columns = columns;
	this->rows = rows;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void ArrayDrawable::setArray(const std::vector<sf::Drawable*>& drawables)
{
	this->drawables = drawables;
}

void ArrayDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			sf::RenderStates currentStates = states;
			sf::Transform translate{};
			translate.translate(offsetX * x, offsetY * y);
			currentStates.transform *= translate;
			target.draw(*drawables.at(x + y * columns), currentStates);
		}
	}
}
