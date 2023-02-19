#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class Buttons
{
private:
	Rectangle rectangle;
	Color baseColor;
	Color color;
	Color textColor;
	string text;
	int fontSize;
	Font fontbutton;
	Texture2D textureButton;
	Sound clickSound;

public:
	Buttons(
		Rectangle rectangle, 
		Color baseColor,
		string text,
		int fontSize
		);

	~Buttons();

	void DrawButton();
	bool IsButtonPressed();

};