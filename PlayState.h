#pragma once

#include <cstdlib>

#include <SFML/Audio.hpp>

#include "State.h"
#include "Field.h"
#include "LineDrawable.h"
#include "SnowParticleSystem.h"
#include "StandardSelectionSet.h"
#include "ArrayDrawable.h"

class PlayState : public State
{
public:
	void enter() override;
	void exit() override;
	void handleEvent(sf::Event& e) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
private:
	void restart();

	struct Controls
	{
		struct PressControl
		{
			int timerStart;
			int timer;
			bool pressed;

			PressControl() : timerStart{ 15 }, timer{ 0 }, pressed{ false } {}

			void press()
			{
				timer = timerStart;
				pressed = true;
			}

			void unpress()
			{
				pressed = false;
			}

			bool isPressed()
			{
				return timer <= 0 && pressed;
			}

			void update()
			{
				--timer;
			}
		} moveLeft, moveRight, rotateCC, rotateC, sink;

		void update()
		{
			moveLeft.update();
			moveRight.update();
			rotateCC.update();
			rotateC.update();
			sink.update();
		}
	} controls;

	int horizontalMoves;
	int verticalMoves;
	int rotations;
	Field field;
	StandardSelectionSet set;
	Selection randomSelection();

	SnowParticleSystem snowSystem;

	sf::Music music;
};

