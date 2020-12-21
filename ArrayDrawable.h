#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class ArrayDrawable : public sf::Drawable
{
public:
	ArrayDrawable();

	void setDimensions(int columns, int rows, float offsetX, float offsetY);

	void setArray(const std::vector<sf::Drawable*>& drawables);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	int columns, rows;
	float offsetX, offsetY;
	std::vector<sf::Drawable*> drawables;
};

