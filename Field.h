#pragma once

#include <vector>
#include <functional>
#include <array>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "ArrayDrawable.h"
#include "SquareDrawable.h"
#include "Square.h"
#include "Selection.h"

class Field : public sf::Drawable
{
public:
	Field();
	~Field();

	void update();

	void setSize(float squareSize, float squareBorderRatio, float squareOffset);

	void setPosition(float x, float y);

	sf::Vector2f computeSize();

	void moveSelection(bool left);
	void sinkSelection();
	void rotateSelection(bool cc);
	bool tryCreateSelection(const Selection& selection);

	bool hasLost();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	constexpr static int columns = 10;
	constexpr static int rows = 20;
private:
	bool withinBounds(int x, int y);
	std::array<std::array<Square, columns>, rows> squares;

	bool isPaused();
	void updateSelection();
	void clearSelection();
	bool placeSelection();
	void unplaceSelection();
	void orientSelection(bool cc);
	void checkRows();
	void animateClearRows(const std::vector<int>& rowsCleared);
	std::vector<int> rowsCleared;
	float animationTimer;
	void clearRow(int r);
	int selectionX, selectionY;
	Selection selection;
	bool hasSelection;
	int timer;
	float timeGap;
	bool lost;

	float squareSize, squareBorderRatio, squareOffset, x, y;
	ArrayDrawable arrayDrawable;
	std::vector<sf::Drawable*> arrayDrawableVector;
	std::array<std::array<SquareDrawable, columns>, rows> squareDrawables;
};