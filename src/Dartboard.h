#pragma once
#include "oxygine-framework.h"
#include <functional>
#include "Range.h"

using namespace oxygine;

class Dartboard {
public:

	static const int RANGE_WIDTH = 360 / 20;
	static std::vector<Range> _ranges;
	static std::vector<int> _scores;
	static int calcScore(Vector2 posDart, Vector2 screenCenter);
	static void	init();
};
