#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

class LineDrawable : public sf::Drawable
{
public:
	LineDrawable();

	void setThickness(float thickness);

	void setColor(sf::Color color);

	void setPoints(sf::Vector2f p0, sf::Vector2f p1);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape rect;
};

