#include "scenes/Menu.h"

Buttons* buttonPlay;
Buttons* buttonRules;
Buttons* buttonOptions;
Buttons* buttonCredits;
Buttons* buttonExit;

static Texture2D textureMenuBackground;
static Texture2D textureMenuButton;

static Font titleFontMenu;

void MenuScene()
{
	if (!isButtonsCreated)
	{
		LoadResourcesMouse();
		CreateButtons();
		isButtonsCreated = true;
	}

	if (!menuRosurcesLoaded)
	{
		LoadResourcesMenu();
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
		UnloadResourcesMenu();
	}
	else if (buttonRules->IsButtonPressed())
	{
		setGameScene(GameScene::Rules);
		UnloadResourcesMenu();
	}
	else if (buttonOptions->IsButtonPressed())
	{
		setGameScene(GameScene::Options);
		UnloadResourcesMenu();
	}
	else if (buttonCredits->IsButtonPressed())
	{
		setGameScene(GameScene::Credits);
		UnloadResourcesMenu();
	}
	else if (buttonExit->IsButtonPressed())
	{
		setGameScene(GameScene::Exit);
		UnloadResourcesMenu();
	}
}

void DrawMenu()
{
	BeginDrawing();
	ClearBackground(BLACK);


	DrawTexturePro(textureMenuBackground,
		{ 0, 0, 128,128 },
		{ 0, 0, textureMenuBackground.width * 6.25f, textureMenuBackground.height * 6.25f },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(titleFontMenu, "WHERE IS MY TIME!?",
		{ (GetPercentageScreenWidth(50) - (MeasureText("WHERE IS MY TIME!?", 60)) / 2), GetPercentageScreenHeight(10) },
		50, GetPercentageScreenWidth(1), RED);

	buttonPlay->DrawButton();
	buttonRules->DrawButton();
	buttonOptions->DrawButton();
	buttonCredits->DrawButton();
	buttonExit->DrawButton();

	DrawText("0.8", GetScreenWidth() - MeasureText("0.8", 40), GetScreenHeight() - MeasureText("0.8", 20), 20, WHITE);

	DrawMouse();

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

void LoadResourcesMenu()
{
	textureMenuBackground = LoadTexture("res/textures/menuBackground.png");
	titleFontMenu = LoadFont("res/fonts/NEONLEDLight.otf");

	menuRosurcesLoaded = true;
}

void UnloadResourcesMenu()
{
	UnloadTexture(textureMenuBackground);

	menuRosurcesLoaded = false;
}