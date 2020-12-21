#include "Selection.h"

Selection::Selection()
{
	for (int y = 0; y < selectionSize; ++y)
	{
		for (int x = 0; x < selectionSize; ++x)
		{
			squares[y][x] = Square::Empty;
		}
	}
}

void rotateSelectionAboutPivot(Selection& selection, bool cc)
{
	int w = selection.pivotWidth;
	int hw = w / 2;
	int xOff = selection.pivotX - hw;
	int yOff = selection.pivotY - hw;
	--w;
	std::function<void(int, int)> rotCC =
		[&selection, w, xOff, yOff](int x, int y)
	{
		Square temp = selection.squares[y + yOff][x + xOff];
		selection.squares[y + yOff][x + xOff] = selection.squares[x + yOff][w - y + xOff];
		selection.squares[x + yOff][w - y + xOff] = selection.squares[w - y + yOff][w - x + xOff];
		selection.squares[w - y + yOff][w - x + xOff] = selection.squares[w - x + yOff][y + xOff];
		selection.squares[w - x + yOff][y + xOff] = temp;
	};
	std::function<void(int, int)> rotC =
		[&selection, w, xOff, yOff](int x, int y)
	{
		Square temp = selection.squares[y + yOff][x + xOff];
		selection.squares[y + yOff][x + xOff] = selection.squares[w - x + yOff][y + xOff];
		selection.squares[w - x + yOff][y + xOff] = selection.squares[w - y + yOff][w - x + xOff];
		selection.squares[w - y + yOff][w - x + xOff] = selection.squares[x + yOff][w - y + xOff];
		selection.squares[x + yOff][w - y + xOff] = temp;
	};
	auto rot = cc ? rotCC : rotC;

	int start = xOff;
	int end = w;
	int j = yOff;
	while (end > start)
	{
		for (int i = start; i < end; ++i)
		{
			rot(i, j);
		}
		++start;
		--end;
		++j;
	}
}
