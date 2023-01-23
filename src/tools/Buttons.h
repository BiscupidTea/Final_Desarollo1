#pragma once
#include "raylib.h"
#include "tools.h"
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

public:
	Buttons(
		Rectangle rectangle, 
		Color baseColor,
		string text,
		int fontSize
		);

	void DrawButton();
	bool IsButtonPressed();

};