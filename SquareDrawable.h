#pragma once

#include <SFML/Graphics.hpp>

class SquareDrawable : public sf::Drawable
{
public:
	SquareDrawable();

	void setSize(float width, float borderRatio);

	void setScale(float scale);

	void setColor(sf::Color color);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape outer;
	sf::RectangleShape inner;
};