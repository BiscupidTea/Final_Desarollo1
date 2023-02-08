#include "Credits.h"

Buttons* buttonExitCredits;

void CreditsScene()
{
	if (!isCreditsButtonsCreated)
	{
		CreateButtonsCredits();
		isCreditsButtonsCreated = true;
	}

	UpdateCredits();

	DrawCredits();
}

void UpdateCredits()
{
	if (buttonExitCredits->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
	}
}

void DrawCredits()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("Game made by",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("Game made by", 40)) / 2),
		static_cast<int>(GetPercentageScreenHeight(10)),
		40, GREEN);

	DrawText("Enzo Coletta",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("Enzo Coletta", 30)) / 2),
		static_cast<int>(GetPercentageScreenHeight(20)),
		30, GREEN);

	DrawText("Tools Used",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("Tools Used", 40)) / 2),
		static_cast<int>(GetPercentageScreenHeight(40)),
		40, GREEN);

	DrawText("Raylib",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("Raylib", 30)) / 2),
		static_cast<int>(GetPercentageScreenHeight(50)),
		30, GREEN);

	buttonExitCredits->DrawButton();

	DrawText("0.5", GetScreenWidth() - MeasureText("0.5", 40), GetScreenHeight() - MeasureText("0.5", 20), 20, WHITE);
	DrawMouse();

	EndDrawing();
}

void CreateButtonsCredits()
{
	buttonExitCredits = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
	cout << "exit created" << endl;
}