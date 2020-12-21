#include "Field.h"

Field::Field() : timer{ 0 }, timeGap{ 35.0f }, animationTimer{ 0.0f }, selectionX{ 0 }, selectionY{ 0 }, hasSelection{ false }, lost{ false }, 
squareSize{ 0.0f }, squareBorderRatio{ 0.0f }, squareOffset{ 0.0f }, x{ 0.0f }, y{ 0.0f }
{
	arrayDrawableVector.resize(rows * columns);
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			squares[y][x] = Square::Empty;
		}
	}
}

Field::~Field()
{
}

void Field::update()
{
	if (hasSelection && !isPaused())
	{
		++timer;
		if (timer % (int)(timeGap) == 0)
		{
			updateSelection();
		}
	}
	bool shouldAnimate = false;
	if (animationTimer > 0.0f)
	{
		float animationDuration = std::max(0.3f, timeGap / 80.0f);
		float timerStep = 1.0 / (60.0f * animationDuration);
		animationTimer -= timerStep;
		if (animationTimer <= 0.0f)
		{
			for (auto it = rowsCleared.begin(); it != rowsCleared.end(); ++it)
			{
				clearRow(*it);
			}
			rowsCleared.clear();
		}
		else
		{
			shouldAnimate = true;
		}
	}

	int i = 0;
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			SquareDrawable& sd = squareDrawables[y][x];
			sd.setSize(squareSize, squareBorderRatio);
			sd.setScale(1.0f);
			sd.setColor(squareColor(squares[y][x]));
			arrayDrawableVector.at(i) = &sd;
			++i;
		}
	}
	if (shouldAnimate)
	{
		for (int x = 0; x < columns; ++x)
		{
			float t = std::max(0.0f, std::min(1.0f, 2.0f * animationTimer - (float)(columns - x) / columns));
			for (auto it = rowsCleared.begin(); it != rowsCleared.end(); ++it)
			{
				squareDrawables[*it][x].setScale(t);
			}
		}
	}
	arrayDrawable.setDimensions(columns, rows, squareOffset + squareSize, squareOffset + squareSize);
	arrayDrawable.setArray(arrayDrawableVector);
}

void Field::setSize(float squareSize, float squareBorderRatio, float squareOffset)
{
	this->squareSize = squareSize;
	this->squareBorderRatio = squareBorderRatio;
	this->squareOffset = squareOffset;
}

void Field::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

sf::Vector2f Field::computeSize()
{
	return sf::Vector2f{ columns * (squareOffset + squareSize) - squareOffset,
						 rows * (squareOffset + squareSize) - squareOffset };
}

void Field::moveSelection(bool left)
{
	if (isPaused()) return;
	unplaceSelection();
	int oldSelectionX = selectionX;
	selectionX += left ? -1 : 1;
	if (!placeSelection())
	{
		selectionX = oldSelectionX;
		placeSelection();
	}
}

void Field::sinkSelection()
{
	if (isPaused()) return;
	timer = 0;
	updateSelection();
}

void Field::rotateSelection(bool cc)
{
	if (isPaused()) return;
	unplaceSelection();
	orientSelection(cc);
	if (!placeSelection())
	{
		--selectionX;
		if (!placeSelection())
		{
			--selectionX;
			if (!placeSelection())
			{
				selectionX += 3;
				if (!placeSelection())
				{
					++selectionX;
					if (!placeSelection())
					{
						selectionX -= 2;
						orientSelection(!cc);
						placeSelection();
					}
				}
			}
		}
	}
}

bool Field::tryCreateSelection(const Selection& selection)
{
	if (isPaused()) return false;
	if (!hasSelection && !lost)
	{
		hasSelection = true;
		selectionX = (columns - selection.pivotWidth) / 2;
		selectionY = -selection.pivotWidth;
		this->selection = selection;
		placeSelection();
		return true;
	}
	return false;
}

bool Field::hasLost()
{
	return lost;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform translate{};
	translate.translate(x, y);
	states.transform *= translate;
	target.draw(arrayDrawable, states);
}

bool Field::withinBounds(int x, int y)
{
	return x >= 0 && y >= 0 && x < columns && y < rows;
}

bool Field::isPaused()
{
	return lost || animationTimer > 0.0f;
}

void Field::updateSelection()
{
	unplaceSelection();
	++selectionY;
	if (!placeSelection())
	{
		--selectionY;
		placeSelection();
		clearSelection();
		if (selectionY < 0)
		{
			lost = true;
		}
		else
		{
			checkRows();
		}
	}
}

void Field::clearSelection()
{
	hasSelection = false;
	timer = 0;
}

bool Field::placeSelection()
{
	int fieldY = selectionY;
	for (int y = 0; y < selectionSize; ++y)
	{
		int fieldX = selectionX;
		for (int x = 0; x < selectionSize; ++x)
		{
			if (selection.squares[y][x] != Square::Empty && !((withinBounds(fieldX, fieldY) && squares[fieldY][fieldX] == Square::Empty) || (fieldY < 0 && fieldX >= 0 && fieldX < columns)))
			{
				return false;
			}
			++fieldX;
		}
		++fieldY;
	}

	fieldY = selectionY;
	for (int y = 0; y < selectionSize; ++y)
	{
		int fieldX = selectionX;
		for (int x = 0; x < selectionSize; ++x)
		{
			if (fieldY >= 0 && selection.squares[y][x] != Square::Empty)
				squares[fieldY][fieldX] = selection.squares[y][x];
			++fieldX;
		}
		++fieldY;
	}
	return true;
}

void Field::unplaceSelection()
{
	int fieldY = selectionY;
	for (int y = 0; y < selectionSize; ++y)
	{
		int fieldX = selectionX;
		for (int x = 0; x < selectionSize; ++x)
		{
			if (withinBounds(fieldX, fieldY) && selection.squares[y][x] != Square::Empty)
			{
				squares[fieldY][fieldX] = Square::Empty;
			}
			++fieldX;
		}
		++fieldY;
	}
}

void Field::orientSelection(bool cc)
{
	if (hasSelection)
		rotateSelectionAboutPivot(selection, cc);
}

void Field::checkRows()
{
	std::vector<int> rowsCleared;
	for (int r = 0; r < rows; ++r)
	{
		bool allSolid = true;
		for (int i = 0; i < columns; ++i)
		{
			if (squares[r][i] == Square::Empty)
			{
				allSolid = false;
			}
		}
		if (allSolid)
		{
			rowsCleared.push_back(r);
		}
	}
	animateClearRows(rowsCleared);
}

void Field::animateClearRows(const std::vector<int>& rowsCleared)
{
	this->rowsCleared = rowsCleared;
	if (rowsCleared.size() > 0)
		animationTimer = 1.0f;
}

void Field::clearRow(int r)
{
	for (int y = r - 1; y >= 0; --y)
	{
		squares[y + 1] = squares[y];
	}
	if (timeGap > 5.5f)
		timeGap -= 0.6f;
}
