#include "Buttons.h"

Buttons::Buttons(Rectangle rectangle, Color baseColor, string text, int fontSize)
{
	this->rectangle = rectangle;
	this->baseColor = baseColor;
	this->color = baseColor;
	this->text = text;
	this->fontSize = fontSize;
	this->textureButton = LoadTexture("res/textures/button.png");
	this->fontbutton = LoadFont("res/fonts/DS-DIGI.TTF");
	this->clickSound = LoadSound("res/sounds/sfx/selected.ogg");
}

Buttons::~Buttons()
{
	UnloadTexture(textureButton);
	UnloadFont(fontbutton);
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

	DrawTexturePro(textureButton,
		{ 0, 0, 64,64 },
		{ rectangle.x, rectangle.y, rectangle.width, rectangle.height },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontbutton, text.c_str(),
		{ (rectangle.x + (rectangle.width / 2) - ((MeasureText(text.c_str(), fontSize)) / 2)),
		(rectangle.y + (rectangle.height / 2) - (fontSize / 2)), }, 
		static_cast<float>(fontSize), GetPercentageScreenWidth(0.3f), color);
}

bool Buttons::IsButtonPressed()
{
	if (CheckMouseRectangleColition(rectangle))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			SetSoundVolume(clickSound, getVolumeSFX());
			PlaySound(clickSound);
			return true;
		}
	}

	return false;
}