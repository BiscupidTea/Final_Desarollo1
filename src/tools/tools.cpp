#include "tools.h"

float GetPercentageScreenHeight(float percentage)
{
	float valueToReturn = 0;
	valueToReturn = static_cast<float>(GetScreenHeight() / 100);
	valueToReturn *= percentage;
	return valueToReturn;
}

float GetPercentageScreenWidth(float percentage)
{
	float valueToReturn = 0;
	valueToReturn = static_cast<float>(GetScreenWidth() / 100);
	valueToReturn *= percentage;
	return valueToReturn;
}

void DrawLinesScreen()
{

	for (float i = 0; i < GetScreenWidth(); i ++)
	{
		DrawLine(static_cast<int>(GetPercentageScreenWidth(i)), 0, static_cast<int>(GetPercentageScreenWidth(i)), GetScreenHeight(), BLACK);
	}

	for (float i = 0; i < GetScreenHeight(); i ++)
	{
		DrawLine(0, static_cast<int>(GetPercentageScreenHeight(i)), GetScreenWidth(), static_cast<int>(GetPercentageScreenHeight(i)), BLACK);
	}

	DrawLine(static_cast<int>(GetPercentageScreenWidth(50)), 0, static_cast<int>(GetPercentageScreenWidth(50)), GetScreenHeight(), RED);
	DrawLine(0, static_cast<int>(GetPercentageScreenHeight(50)), GetScreenWidth(), static_cast<int>(GetPercentageScreenHeight(50)), RED);
}