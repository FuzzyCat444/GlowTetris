#include "PlayState.h"

void PlayState::enter()
{
	restart();

	snowSystem = SnowParticleSystem{};
	snowSystem.init(50, 800.0f, 800.0f);

	music.openFromFile("tetris_theme_christmas.ogg");
	music.setLoop(true);
	music.play();
}

void PlayState::exit()
{
	music.stop();
}

void PlayState::handleEvent(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Left)
		{
			controls.moveLeft.press();
			--horizontalMoves;
		}
		if (e.key.code == sf::Keyboard::Right)
		{
			controls.moveRight.press();
			++horizontalMoves;
		}
		if (e.key.code == sf::Keyboard::Up)
		{
			controls.rotateC.press();
			++rotations;
		}
		if (e.key.code == sf::Keyboard::Down)
		{
			controls.rotateCC.press();
			--rotations;
		}
		if (e.key.code == sf::Keyboard::Space)
		{
			controls.sink.press();
			++verticalMoves;
		}
	}
	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Left)
			controls.moveLeft.unpress();
		if (e.key.code == sf::Keyboard::Right)
			controls.moveRight.unpress();
		if (e.key.code == sf::Keyboard::Up)
			controls.rotateC.unpress();
		if (e.key.code == sf::Keyboard::Down)
			controls.rotateCC.unpress();
		if (e.key.code == sf::Keyboard::Space)
			controls.sink.unpress();
	}
}

static int selectionNum = 0;
void PlayState::update()
{

	if (controls.moveLeft.isPressed())
		--horizontalMoves;
	if (controls.moveRight.isPressed())
		++horizontalMoves;
	if (controls.rotateC.isPressed())
		++rotations;
	if (controls.rotateCC.isPressed())
		--rotations;
	if (controls.sink.isPressed())
		++verticalMoves;
	controls.update();

	field.tryCreateSelection(randomSelection());
	if (field.hasLost())
	{
		restart();
	}

	selectionNum++;
	while (horizontalMoves != 0)
	{
		bool less = horizontalMoves < 0;
		field.moveSelection(less);
		horizontalMoves += less ? 1 : -1;
	}
	while (rotations != 0)
	{
		bool cc = rotations < 0;
		field.rotateSelection(cc);
		rotations += cc ? 1 : -1;
	}
	while (verticalMoves > 0)
	{
		field.sinkSelection();
		--verticalMoves;
	}
	field.update();

	snowSystem.update();
}

void PlayState::draw(sf::RenderTarget& target)
{
	target.draw(snowSystem);

	sf::Vector2f fieldSize = field.computeSize();
	sf::Vector2f fieldPosition = (sf::Vector2f{ 800.0f, 800.0f } -fieldSize) / 2.0f;

	sf::RectangleShape bounds;
	bounds.setFillColor(sf::Color::Transparent);

	bounds.setOutlineThickness(5.0f);
	bounds.setOutlineColor(sf::Color::White);
	bounds.setPosition(5.0f, 5.0f);
	bounds.setSize(sf::Vector2f{ 800.0f, 800.0f } - sf::Vector2f{ 10.0f, 10.0f });
	target.draw(bounds);

	bounds.setOutlineThickness(6.0f);
	bounds.setOutlineColor(sf::Color::Green);
	bounds.setPosition(fieldPosition - sf::Vector2f{ 20.0f, 20.0f });
	bounds.setSize(fieldSize + sf::Vector2f{ 40.0f, 40.0f });
	target.draw(bounds);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setPosition(fieldPosition - sf::Vector2f{ 40.0f, 40.0f });
	bounds.setSize(fieldSize + sf::Vector2f{ 80.0f, 80.0f });
	target.draw(bounds);

	field.setPosition(fieldPosition.x, fieldPosition.y);
	target.draw(field);
}

void PlayState::restart()
{
	controls = Controls{};

	horizontalMoves = 0;
	field = Field{};
	field.setSize(20.0f, 0.5f, 11.5f);
}

Selection PlayState::randomSelection()
{
	int id = rand() % 7;
	Selection selection;
	switch (id)
	{
	case 0:
		selection = set.boxSelection();
		break;
	case 1:
		selection = set.lineSelection();
		break;
	case 2:
		selection = set.tSelection();
		break;
	case 3:
		selection = set.squiggleSelection();
		break;
	case 4:
		selection = set.reverseSquiggleSelection();
		break;
	case 5:
		selection = set.lSelection();
		break;
	case 6:
		selection = set.reverseLSelection();
		break;
	}
	int rots = rand() % 4;
	for (int i = 0; i < rots; ++i)
	{
		rotateSelectionAboutPivot(selection, true);
	}
	return selection;
}
