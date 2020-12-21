#pragma once

#include <array>

#include <functional>

#include "Square.h"

constexpr int selectionSize = 5;

struct Selection
{
	Selection();

	int pivotX, pivotY, pivotWidth;
	std::array<std::array<Square, selectionSize>, selectionSize> squares;
};

void rotateSelectionAboutPivot(Selection& selection, bool cc);
