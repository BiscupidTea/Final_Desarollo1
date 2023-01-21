#include "Buttons.h"

Buttons::Buttons(Rectangle rectangle, Color baseColor, string text, int fontSize)
{
	this->rectangle = rectangle;
	this->baseColor = baseColor;
	this->color = baseColor;
	this->text = text;
	this->fontSize = fontSize;
}

void Buttons::DrawButton()
{

	if (CheckMouseRectangleColition(rectangle))
	{
		color = WHITE;
	}
	else
	{
		color = baseColor;
	}

	DrawRectangleRec(rectangle,color);
	DrawText(text.c_str(), 
		rectangle.x - MeasureText(text.c_str(), fontSize)/2,
		rectangle.y - MeasureText(text.c_str(), fontSize),
		fontSize, color);
}

bool Buttons::IsButtonPressed()
{
	if (CheckMouseRectangleColition(rectangle))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}

	return false;
}