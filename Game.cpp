#include "Game.h"
#include "PlayState.h"

Game::Game()
{
}

void Game::start()
{
	const sf::Vector2u screenSize{ 800, 800 };
	sf::RenderWindow window(sf::VideoMode{ screenSize.x, screenSize.y }, "Glow Tetris by Harrison B", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Shader shader{};
	shader.loadFromFile("glow.frag", sf::Shader::Fragment);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderTexture renderTexture;
	renderTexture.create(screenSize.x, screenSize.y, settings);
	sf::Sprite renderSprite;
	renderSprite.setTexture(renderTexture.getTexture());

	stateManager.addState(playStateID, new PlayState());
	stateManager.switchState(playStateID);

	sf::Clock clock;
	sf::Time oldTime = clock.getElapsedTime();
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time timeStep = sf::seconds(1.0f / 40.0f);
	while (window.isOpen()) 
	{
		sf::Time newTime = clock.getElapsedTime();
		deltaTime += newTime - oldTime;
		oldTime = newTime;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			stateManager.handleEvent(e);
		}
		while (deltaTime >= timeStep) 
		{
			stateManager.update();
			deltaTime -= timeStep;
		}

		renderTexture.clear();
		stateManager.draw(renderTexture);
		renderTexture.display();

		shader.setUniform("texture", sf::Shader::CurrentTexture);
		shader.setUniform("screenSize", sf::Glsl::Ivec2(screenSize));
		sf::RenderStates renderStates{ &shader };
		window.clear();
		window.draw(renderSprite, renderStates);
		window.display();
	}
}
