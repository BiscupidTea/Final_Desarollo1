#include "scenes/Menu.h"

Buttons* buttonPlay;

Buttons* buttonRules;

Buttons* buttonOptions;

Buttons* buttonCredits;

Buttons* buttonExit;

void MenuScene()
{
	if (!isButtonsCreated)
	{
		CreateButtons();
		isButtonsCreated = true;
	}

	UpdateMenu();

	DrawMenu();
}

void UpdateMenu()
{
	if (buttonPlay->IsButtonPressed())
	{
		setGameScene(GameScene::GameLoop);
		InitGameLoop();
	}
	else if(buttonRules->IsButtonPressed())
	{
		setGameScene(GameScene::Rules);
	}
	else if (buttonOptions->IsButtonPressed())
	{
		setGameScene(GameScene::Options);
	}
	else if (buttonCredits->IsButtonPressed())
	{
		setGameScene(GameScene::Credits);
	}
	else if (buttonExit->IsButtonPressed())
	{
		setGameScene(GameScene::Exit);
	}
}

void DrawMenu()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("WHERE IS MY TIME!?",
		static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("WHERE IS MY TIME!?", 50)) / 2),
		static_cast<int>(GetPercentageScreenHeight(10)),
		50, GREEN);

	buttonPlay->DrawButton();
	buttonRules->DrawButton();
	buttonOptions->DrawButton();
	buttonCredits->DrawButton();
	buttonExit->DrawButton();

	DrawText("0.5", GetScreenWidth() - MeasureText("0.5", 40), GetScreenHeight() - MeasureText("0.5", 20), 20, WHITE);

	EndDrawing();
}

void CreateButtons()
{
	buttonPlay = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(25),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(7) },
		RED, "play", 30);

	buttonRules = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(40),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(7) },
		RED, "Rules", 30);

	buttonOptions = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(55),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(7) },
		RED, "Options", 30);

	buttonCredits = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(70),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(7) },
		RED, "Credits", 30);

	buttonExit = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
}