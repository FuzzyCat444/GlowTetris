#include "SquareDrawable.h"

SquareDrawable::SquareDrawable()
{
	inner.setFillColor(sf::Color::Black);
}

void SquareDrawable::setSize(float width, float borderRatio)
{
	outer.setSize(sf::Vector2f{ width, width });
	outer.setOrigin(outer.getSize() / 2.0f);
	outer.setPosition(outer.getOrigin());
	float border = borderRatio * 0.5f * width;
	inner.setSize(sf::Vector2f{ width - border * 2.0f, width - border * 2.0f });
	inner.setOrigin(inner.getSize() / 2.0f);
	inner.setPosition(outer.getOrigin());
}

void SquareDrawable::setScale(float scale)
{
	outer.setScale(scale, scale);
	inner.setScale(scale, scale);
}

void SquareDrawable::setColor(sf::Color color)
{
	outer.setFillColor(color);
}

void SquareDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (outer.getFillColor() != sf::Color::Black)
	{
		target.draw(outer, states);
		target.draw(inner, states);
	}
}
