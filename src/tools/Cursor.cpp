#include "Cursor.h"

#include "raylib.h"

static Texture2D textureCursorUp;
static Texture2D textureCursorDown;

void LoadResourcesMouse()
{
	textureCursorUp = LoadTexture("res/textures/cursorUp.png");
	textureCursorDown = LoadTexture("res/textures/cursorDown.png");
}

void UnloadResourcesMouse()
{
	UnloadTexture(textureCursorUp);
	UnloadTexture(textureCursorDown);
}

void DrawMouse()
{
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		DrawTexturePro(textureCursorUp,
			{ 0,0, 64, 64 },
			{ static_cast<float>(GetMouseX()) ,static_cast<float>(GetMouseY()), 64, 64 },
			{ 0,0 },
			0, WHITE
		);
	}
	else
	{
		DrawTexturePro(textureCursorDown,
			{ 0,0, 64, 64 },
			{ static_cast<float>(GetMouseX()) ,static_cast<float>(GetMouseY()), 64, 64 },
			{ 0,0 },
			0, WHITE
		);
	}
}