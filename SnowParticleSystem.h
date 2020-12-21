#pragma once

#include <cmath>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>

class SnowParticleSystem : public sf::Drawable
{
public:
	SnowParticleSystem();

	void init(int numFlakes, float endX, float endY);

	void update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	struct Snowflake;

	std::vector<Snowflake> snowflakes;

	struct Snowflake : public sf::Drawable
	{
		sf::Vector2f pos;
		float endY;
		float t;
		sf::CircleShape flake;

		Snowflake(float startX, float startY, float endY, float startT) : pos{ startX, startY }, endY{ endY }, t{ startT } {}

		void update()
		{
			float r = 2.5f;
			flake.setOrigin(r, r);
			flake.setFillColor(sf::Color::White);
			flake.setRadius(r);
			pos += sf::Vector2f{ std::cos(t) * 0.5f, 0.5f };
			flake.setPosition(pos);
			if (pos.y - r >= endY)
			{
				pos.y = -r;
			}
			t += 1 / 60.0f;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(flake);
		}
	};
};

