#pragma once
#include"raylib.h"

namespace Game
{

	float GetPercentageScreenHeight(
		float percentage
	);

	float GetPercentageScreenWidth(
		float percentage
	);

	void DrawLinesScreen(

	);

	bool CheckMouseRectangleColition(
		Rectangle rectangle
	);

}