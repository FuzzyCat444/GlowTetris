#include "LineDrawable.h"

LineDrawable::LineDrawable() : rect{}
{
}

void LineDrawable::setThickness(float thickness)
{
	rect.setSize(sf::Vector2f{ rect.getSize().x, thickness });
}

void LineDrawable::setColor(sf::Color color)
{
	rect.setFillColor(color);
}

void LineDrawable::setPoints(sf::Vector2f p0, sf::Vector2f p1)
{
	sf::Vector2f diff = p1 - p0;
	float length = std::hypot(diff.x, diff.y);
	rect.setSize(sf::Vector2f{ -length, rect.getSize().y });
	rect.setOrigin(0.0f, rect.getSize().y / 2.0f);
	rect.setRotation(std::atan2(diff.y, diff.x) * 180.0f / 3.1415926535f - 180.0f);
	rect.setPosition(p0);
}

void LineDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
}
