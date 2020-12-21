#include "SnowParticleSystem.h"

SnowParticleSystem::SnowParticleSystem()
{
}

void SnowParticleSystem::init(int numFlakes, float endX, float endY)
{
	snowflakes.clear();
	for (int i = 0; i < numFlakes; ++i)
	{
		float randX = endX * std::rand() / (float) RAND_MAX;
		float randY = endY * std::rand() / (float) RAND_MAX;
		float randT = 6.28f * std::rand() / (float) RAND_MAX;
		snowflakes.push_back(Snowflake{ randX, randY, endY, randT });
	}
}

void SnowParticleSystem::update()
{
	for (auto it = snowflakes.begin(); it != snowflakes.end(); ++it)
	{
		it->update();
	}
}

void SnowParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto it = snowflakes.begin(); it != snowflakes.end(); ++it)
	{
		target.draw(*it);
	}
}
