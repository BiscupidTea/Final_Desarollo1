#include "Rules.h"

Buttons* buttonExitRules;

static Texture2D textureObstacleTuto;
static Texture2D textureTimerItemTuto;
static Texture2D textureShieldTuto;
static Texture2D texturePostIt;

static Texture2D textureRulesBackground;
static Texture2D textureRulesTitles;
static Font fontTitles;

void RulesScene()
{
	if (!isRulesButtonsCreated)
	{
		CreateButtonsRules();
		isRulesButtonsCreated = true;
	}

	if (!RulesRosurcesLoaded)
	{
		LoadResourcesRules();
	}

	UpdateRules();

	DrawRules();
}

void UpdateRules()
{
	if (buttonExitRules->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
		UnloadResourcesRules();
	}
}

void DrawRules()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawTexturePro(textureRulesBackground,
		{ 0, 0, 128,128 },
		{ 0, 0, textureRulesBackground.width * 6.25f, textureRulesBackground.height * 6.25f },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, "How to survive in Lab", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(10) },
		40, GetPercentageScreenWidth(0.1f), BLACK);

	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(5)), 
		static_cast<int>(GetPercentageScreenHeight(15)), 
		MeasureText("How to survive in Lab", 40), 
		static_cast<int>(GetPercentageScreenHeight(1)), BLACK);

	DrawTextEx( fontTitles, "1) Press SPACE to fly", 
		{GetPercentageScreenWidth(5), GetPercentageScreenHeight(25)}, 
		30, GetPercentageScreenWidth(0.1f), BLACK	);

	DrawTextEx(fontTitles, "2) Press F to shoot (you have 5 shoots only)", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(35) },
		30, GetPercentageScreenWidth(0.1f), BLACK);

	DrawTextEx(fontTitles, "3) Dodge the obstacles (not frendly)", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(45) },
		30, GetPercentageScreenWidth(0.1f), BLACK);

	DrawTexturePro(textureObstacleTuto,
		{ 0, 0, 64,64 },
		{ GetPercentageScreenWidth(70), GetPercentageScreenHeight(42), GetPercentageScreenWidth(8),GetPercentageScreenHeight(8) },
		{ 0,	0, },
		15, WHITE);

	DrawTextEx(fontTitles, "4) Pick up this to increase your time (if ends you lose)", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(55) },
		25, GetPercentageScreenWidth(0.1f), BLACK);

	DrawTexturePro(textureTimerItemTuto,
		{ 0, 0, 64,64 },
		{ GetPercentageScreenWidth(85), GetPercentageScreenHeight(55), GetPercentageScreenWidth(5),GetPercentageScreenHeight(5) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, "5) Pick up Shield if you whant to survive 1 more hit", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(65) },
		25, GetPercentageScreenWidth(0.1f), BLACK);

	DrawTexturePro(textureShieldTuto,
		{ 0, 0, 64,64 },
		{ GetPercentageScreenWidth(85), GetPercentageScreenHeight(65), GetPercentageScreenWidth(5),GetPercentageScreenHeight(5) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, "6) Super important, don't forget", 
		{ GetPercentageScreenWidth(5), GetPercentageScreenHeight(75) },
		30, GetPercentageScreenWidth(0.1f), BLACK);

	DrawTexturePro(texturePostIt,
		{ 0, 0, 64,64 },
		{ GetPercentageScreenWidth(55), GetPercentageScreenHeight(68), GetPercentageScreenWidth(30),GetPercentageScreenHeight(25) },
		{ 0,	0, },
		15, WHITE);

	DrawTextPro(fontTitles, "Press Esc for Pause", 
		{ GetPercentageScreenWidth(58), GetPercentageScreenHeight(79) }, 
		{0,0},
		15, 20, GetPercentageScreenWidth(0.1f),BLACK);


	buttonExitRules->DrawButton();

	DrawText("0.7", GetScreenWidth() - MeasureText("0.7", 40), GetScreenHeight() - MeasureText("0.7", 20), 20, WHITE);
	DrawMouse();

	EndDrawing();
}

void CreateButtonsRules()
{
	buttonExitRules = new Buttons(
		{ GetPercentageScreenWidth(85), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
}

void LoadResourcesRules()
{
	textureObstacleTuto = LoadTexture("res/textures/ObstacleTexture.png");
	textureTimerItemTuto = LoadTexture("res/textures/Timer-item.png");
	textureShieldTuto = LoadTexture("res/textures/shield-item.png");
	texturePostIt = LoadTexture("res/textures/postiit.png");

	textureRulesBackground = LoadTexture("res/textures/simpleBackground.png");
	textureRulesTitles = LoadTexture("res/textures/button.png");

	fontTitles = LoadFont("res/fonts/JMH Typewriter.otf");

	RulesRosurcesLoaded = true;
}

void UnloadResourcesRules()
{
	UnloadTexture(textureObstacleTuto);
	UnloadTexture(textureTimerItemTuto);
	UnloadTexture(textureShieldTuto);
	UnloadTexture(texturePostIt);

	UnloadTexture(textureRulesBackground);
	UnloadTexture(textureRulesTitles);

	RulesRosurcesLoaded = false;
}