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

	DrawRectangleRec(rectangle, color);

	DrawText(text.c_str(),
		static_cast<int>(rectangle.x + (rectangle.width / 2) - ((MeasureText(text.c_str(), fontSize)) / 2)),
		static_cast<int>(rectangle.y + (rectangle.height / 2) - (fontSize / 2)),
		fontSize, GREEN);
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