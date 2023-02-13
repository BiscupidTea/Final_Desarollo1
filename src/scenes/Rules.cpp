#include "Rules.h"

Buttons* buttonExitRules;

static Texture2D texturePlayerTuto;
static Texture2D textureBulletTuto;
static Texture2D textureObstacleTuto;
static Texture2D textureTimerTuto;
static Texture2D textureTimerItemTuto;
static Texture2D textureShieldTuto;

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

	buttonExitRules->DrawButton();

	DrawText("0.7", GetScreenWidth() - MeasureText("0.7", 40), GetScreenHeight() - MeasureText("0.7", 20), 20, WHITE);
	DrawMouse();

	EndDrawing();
}

void CreateButtonsRules()
{
	buttonExitRules = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
}

void LoadResourcesRules()
{
	texturePlayerTuto = LoadTexture("res/textures/metalBackground.png");
	textureBulletTuto = LoadTexture("res/textures/metalBackground.png");
	textureObstacleTuto = LoadTexture("res/textures/metalBackground.png");
	textureTimerTuto = LoadTexture("res/textures/metalBackground.png");
	textureTimerItemTuto = LoadTexture("res/textures/metalBackground.png");
	textureShieldTuto = LoadTexture("res/textures/metalBackground.png");

	textureRulesBackground = LoadTexture("res/textures/metalBackground.png");
	textureRulesTitles = LoadTexture("res/textures/button.png");

	fontTitles = LoadFont("res/fonts/DS-DIGI.TTF");

	RulesRosurcesLoaded = true;
}

void UnloadResourcesRules()
{
	UnloadTexture(texturePlayerTuto);
	UnloadTexture(textureBulletTuto);
	UnloadTexture(textureObstacleTuto);
	UnloadTexture(textureTimerTuto);
	UnloadTexture(textureTimerItemTuto);
	UnloadTexture(textureShieldTuto);
	UnloadTexture(textureRulesBackground);
	UnloadTexture(textureRulesTitles);

	RulesRosurcesLoaded = false;
}