#include "Credits.h"

void CreditsScene()
{
	UpdateCredits();

	DrawCredits();
}

void UpdateCredits()
{
	if (IsKeyPressed(KEY_ESCAPE))
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

	DrawText("Press Esc to back to Menu", 0, static_cast<int>(GetPercentageScreenHeight(95)), 30, RED);

	DrawText("0.5", GetScreenWidth() - MeasureText("0.5", 40), GetScreenHeight() - MeasureText("0.5", 20), 20, WHITE);

	EndDrawing();
}