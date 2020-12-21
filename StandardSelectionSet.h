#pragma once

#include "Selection.h"

class StandardSelectionSet
{
public:
	Selection boxSelection();
	Selection lineSelection();
	Selection tSelection();
	Selection squiggleSelection();
	Selection reverseSquiggleSelection();
	Selection lSelection();
	Selection reverseLSelection();
};

