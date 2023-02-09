#include "Credits.h"

Buttons* buttonUrlGit;
Buttons* buttonUrlItch;
Buttons* buttonUrlRaylib;
Buttons* buttonExitCredits;

static Texture2D textureCreditsBackground;
static Texture2D textureCreditsTitles;
static Font fontTitles;

void CreditsScene()
{
	if (!isCreditsButtonsCreated)
	{
		CreateButtonsCredits();
		isCreditsButtonsCreated = true;
	}

	if (!CreditsRosurcesLoaded)
	{
		LoadResourcesCredits();
	}

	UpdateCredits();

	DrawCredits();
}

void UpdateCredits()
{
	if (buttonUrlGit->IsButtonPressed())
	{
		OpenURL("https://github.com/BiscupidTea");
	}

	if (buttonUrlItch->IsButtonPressed())
	{
		OpenURL("https://biscupidtea.itch.io/");
	}

	if (buttonUrlRaylib->IsButtonPressed())
	{
		OpenURL("https://www.raylib.com/index.html");
	}

	if (buttonExitCredits->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
		UnloadResourcesCredits();
	}
}

void DrawCredits()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawTexturePro(textureCreditsBackground,
		{ 0, 0, 128,128 },
		{ 0, 0, textureCreditsBackground.width * 6.25f, textureCreditsBackground.height * 6.25f },
		{ 0,	0, },
		0, WHITE);

	//part1
	Vector2 positionTitle1 = {
		(GetPercentageScreenWidth(50) - MeasureText("Game made by", static_cast<int>(GetPercentageScreenWidth(7))) / 2),
		GetPercentageScreenHeight(10) };

	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(50) / 2),
		static_cast<int>(positionTitle1.y),
		static_cast<int>(GetPercentageScreenWidth(50)),
		static_cast<int>(GetPercentageScreenHeight(8)), BLACK);

	DrawTextEx(
		fontTitles, "Game made by", { positionTitle1.x , positionTitle1.y },
		50, GetPercentageScreenWidth(1), GREEN
	);

	//part2
	Vector2 positionName1 = { GetPercentageScreenWidth(10), GetPercentageScreenHeight(25) };

	DrawRectangle(
		static_cast<int>(positionName1.x - GetPercentageScreenWidth(1)),
		static_cast<int>(positionName1.y - GetPercentageScreenHeight(1)),
		static_cast<int>(MeasureText("Enzo Coletta", 50)),
		static_cast<int>(GetPercentageScreenHeight(7)), BLACK);

	DrawTextEx(
		fontTitles, "Enzo Coletta", { positionName1.x , positionName1.y },
		40, GetPercentageScreenWidth(1), GREEN
	);

	buttonUrlGit->DrawButton();
	buttonUrlItch->DrawButton();

	//part3
	Vector2 positionTitle2 = {
	(GetPercentageScreenWidth(50) - MeasureText("Tools Used", static_cast<int>(GetPercentageScreenWidth(7))) / 2),
	GetPercentageScreenHeight(50) };

	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(50) / 2),
		static_cast<int>(positionTitle2.y),
		static_cast<int>(GetPercentageScreenWidth(50)),
		static_cast<int>(GetPercentageScreenHeight(8)), BLACK);

	DrawTextEx(
		fontTitles, "Tools Used", { positionTitle2.x , positionTitle2.y },
		50, GetPercentageScreenWidth(1), GREEN
	);

	//part4
	Vector2 positionName2 = { GetPercentageScreenWidth(10), GetPercentageScreenHeight(65) };

	DrawRectangle(
		static_cast<int>(positionName2.x - GetPercentageScreenWidth(1)),
		static_cast<int>(positionName2.y - GetPercentageScreenHeight(1)),
		static_cast<int>(MeasureText("Raylib", 55)),
		static_cast<int>(GetPercentageScreenHeight(7)), BLACK);

	DrawTextEx(
		fontTitles, "Raylib", { positionName2.x , positionName2.y },
		40, GetPercentageScreenWidth(1), GREEN
	);

	buttonUrlRaylib->DrawButton();

	buttonExitCredits->DrawButton();

	DrawText("0.6", GetScreenWidth() - MeasureText("0.6", 40), GetScreenHeight() - MeasureText("0.6", 20), 20, WHITE);
	DrawMouse();

	EndDrawing();
}

void CreateButtonsCredits()
{
	buttonUrlGit = new Buttons(
		{ GetPercentageScreenWidth(60), GetPercentageScreenHeight(25) - GetPercentageScreenHeight(3),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "GIT", 30);

	buttonUrlItch = new Buttons(
		{ GetPercentageScreenWidth(75), GetPercentageScreenHeight(25) - GetPercentageScreenHeight(3),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(10) },
		RED, "Ithc.io", 30);

	buttonUrlRaylib = new Buttons(
		{ GetPercentageScreenWidth(60), GetPercentageScreenHeight(65) - GetPercentageScreenHeight(3),
		GetPercentageScreenWidth(15), GetPercentageScreenHeight(10) },
		RED, "Page", 30);

	buttonExitCredits = new Buttons(
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
}

void LoadResourcesCredits()
{
	textureCreditsBackground = LoadTexture("res/textures/metalBackground.png");
	textureCreditsTitles = LoadTexture("res/textures/button.png");
	fontTitles = LoadFont("res/fonts/DS-DIGI.TTF");

	CreditsRosurcesLoaded = true;
}

void UnloadResourcesCredits()
{
	UnloadTexture(textureCreditsBackground);
	UnloadTexture(textureCreditsTitles);

	CreditsRosurcesLoaded = false;
}