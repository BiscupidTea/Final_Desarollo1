#include "scenes/Menu.h"

void MenuScene()
{
	optionsButtons button[5];
	CreateButtons(button);

	UpdateMenu(button);

	DrawMenu(button);
}

void UpdateMenu(optionsButtons button[])
{
	for (int i = 0; i < totButtons; i++)
	{
		if (CheckMouseRectangleColition(button[i].rectangle))
		{
			button[i].color = WHITE;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				button[i].selected = true;

				if (button[0].selected)
				{
					setGameScene(GameScene::GameLoop);
					InitGameLoop();
				}
				else if (button[1].selected)
				{
					setGameScene(GameScene::Rules);
				}
				else if (button[2].selected)
				{
					setGameScene(GameScene::Options);
				}
				else if (button[3].selected)
				{
					setGameScene(GameScene::Credits);
				}
				else if (button[4].selected)
				{
					setGameScene(GameScene::Exit);
				}

				button[i].selected = false;
			}
		}
	}
}

void DrawMenu(optionsButtons button[])
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("WHERE IS MY TIME!?",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("WHERE IS MY TIME!?", 50)) / 2),
		static_cast<int>(GetPercentageScreenHeight(10)),
		50, GREEN);

	for (int i = 0; i < totButtons; i++)
	{

		DrawRectangle(
			static_cast<int>(button[i].rectangle.x),
			static_cast<int>(button[i].rectangle.y),
			static_cast<int>(button[i].rectangle.width),
			static_cast<int>(button[i].rectangle.height),
			button[i].color);

		switch (i)
		{
		case 0:
			DrawText("Play", static_cast<int>(button[i].rectangle.x), static_cast<int>(button[i].rectangle.y), 30, GREEN);
			break;
		case 1:
			DrawText("Rules", static_cast<int>(button[i].rectangle.x), static_cast<int>(button[i].rectangle.y), 30, GREEN);
			break;
		case 2:
			DrawText("Options", static_cast<int>(button[i].rectangle.x), static_cast<int>(button[i].rectangle.y), 30, GREEN);
			break;
		case 3:
			DrawText("Credits", static_cast<int>(button[i].rectangle.x), static_cast<int>(button[i].rectangle.y), 30, GREEN);
			break;
		case 4:
			DrawText("Exit", static_cast<int>(button[i].rectangle.x), static_cast<int>(button[i].rectangle.y), 30, GREEN);
			break;
		default:
			break;
		}
	}

	DrawText("0.2", GetScreenWidth() - MeasureText("0.2", 40), GetScreenHeight() - MeasureText("0.2", 20), 20, WHITE);

	EndDrawing();
}

void CreateButtons(optionsButtons button[])
{

	for (int i = 0; i < totButtons; i++)
	{
		button[i].rectangle.height = GetPercentageScreenHeight(7);
		button[i].rectangle.width = GetPercentageScreenWidth(15);

		button[i].color = RED;
		button[i].selected = false;
	}

	button[4].rectangle.width = GetPercentageScreenWidth(10);
	button[4].rectangle.height = GetPercentageScreenWidth(10);

	button[0].rectangle.x = GetPercentageScreenWidth(15);
	button[1].rectangle.x = GetPercentageScreenWidth(15);
	button[2].rectangle.x = GetPercentageScreenWidth(15);
	button[3].rectangle.x = GetPercentageScreenWidth(15);
	button[4].rectangle.x = GetPercentageScreenWidth(85);

	button[0].rectangle.y = GetPercentageScreenHeight(25);
	button[1].rectangle.y = GetPercentageScreenHeight(40);
	button[2].rectangle.y = GetPercentageScreenHeight(55);
	button[3].rectangle.y = GetPercentageScreenWidth(70);
	button[4].rectangle.y = GetPercentageScreenHeight(85);
}