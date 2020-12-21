#include "StandardSelectionSet.h"

Selection StandardSelectionSet::boxSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 2;
	s.squares[0][0] = Square::Yellow;
	s.squares[0][1] = Square::Yellow;
	s.squares[1][0] = Square::Yellow;
	s.squares[1][1] = Square::Yellow;
	return s;
}

Selection StandardSelectionSet::lineSelection()
{
	Selection s{};
	s.pivotX = 2;
	s.pivotY = 2;
	s.pivotWidth = 4;
	s.squares[0][1] = Square::Cyan;
	s.squares[1][1] = Square::Cyan;
	s.squares[2][1] = Square::Cyan;
	s.squares[3][1] = Square::Cyan;
	return s;
}

Selection StandardSelectionSet::tSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 3;
	s.squares[0][1] = Square::Magenta;
	s.squares[1][0] = Square::Magenta;
	s.squares[1][1] = Square::Magenta;
	s.squares[1][2] = Square::Magenta;
	return s;
}

Selection StandardSelectionSet::squiggleSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 3;
	s.squares[0][1] = Square::Green;
	s.squares[0][2] = Square::Green;
	s.squares[1][0] = Square::Green;
	s.squares[1][1] = Square::Green;
	return s;
}

Selection StandardSelectionSet::reverseSquiggleSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 3;
	s.squares[0][0] = Square::Red;
	s.squares[0][1] = Square::Red;
	s.squares[1][1] = Square::Red;
	s.squares[1][2] = Square::Red;
	return s;
}

Selection StandardSelectionSet::lSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 3;
	s.squares[0][0] = Square::Blue;
	s.squares[1][0] = Square::Blue;
	s.squares[1][1] = Square::Blue;
	s.squares[1][2] = Square::Blue;
	return s;
}

Selection StandardSelectionSet::reverseLSelection()
{
	Selection s{};
	s.pivotX = 1;
	s.pivotY = 1;
	s.pivotWidth = 3;
	s.squares[0][2] = Square::White;
	s.squares[1][0] = Square::White;
	s.squares[1][1] = Square::White;
	s.squares[1][2] = Square::White;
	return s;
}
