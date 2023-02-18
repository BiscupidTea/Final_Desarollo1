#include "Options.h"

Buttons* buttonUpVolumeMusicOptions;
Buttons* buttonDownVolumeMusicOptions;
Buttons* buttonUpVolumeSFXOptions;
Buttons* buttonDownVolumeSFXOptions;

Buttons* buttonExitOptions;

static Texture2D textureOptionsBackground;
static Texture2D textureOptionsButton;
static Font fontTitles;

void OptionsScene()
{
	if (!isOptionsButtonsCreated)
	{
		CreateButtonsOptions();
		isOptionsButtonsCreated = true;
	}

	if (!OptionsRosurcesLoaded)
	{
		LoadResourcesOptions();
	}

	UpdateOptions();

	DrawOptions();
}

void UpdateOptions()
{
	if (buttonExitOptions->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
		UnloadResourcesOptions();
	}

	if (buttonUpVolumeMusicOptions->IsButtonPressed())
	{
		setVolumeMusic(getVolumeMusic() + 0.1f);
	}

	if (buttonDownVolumeMusicOptions->IsButtonPressed())
	{
		setVolumeMusic(getVolumeMusic() - 0.1f);
	}

	if (buttonUpVolumeSFXOptions->IsButtonPressed())
	{
		setVolumeSFX(getVolumeSFX() + 0.1f);
	}

	if (buttonDownVolumeSFXOptions->IsButtonPressed())
	{
		setVolumeSFX(getVolumeSFX() - 0.1f);
	}
}

void DrawOptions()
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawTexturePro(textureOptionsBackground,
		{ 0, 0, 128,128 },
		{ 0, 0, textureOptionsBackground.width * 6.25f, textureOptionsBackground.height * 6.25f },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, "Settings",
		{ GetPercentageScreenWidth(50) - MeasureText("Settings", 45) / 2, GetPercentageScreenHeight(5) },
		45, GetPercentageScreenWidth(0.5), BLACK);

	DrawVolumeOptions();

	buttonExitOptions->DrawButton();

	DrawText("0.7", GetScreenWidth() - MeasureText("0.7", 40), GetScreenHeight() - MeasureText("0.7", 20), 20, WHITE);
	DrawMouse();

	EndDrawing();
}

void DrawVolumeOptions()
{
	//music
	int volumeMusic = static_cast<int>(getVolumeMusic() * 10);

	DrawTextEx(fontTitles, "Music", { GetPercentageScreenWidth(50) - MeasureText("Music", 35) / 2, GetPercentageScreenHeight(24) },
		35, GetPercentageScreenWidth(0.5), BLACK);

	DrawTexturePro(textureOptionsButton,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(8) / 2), GetPercentageScreenHeight(30),
			GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, TextFormat("%i", volumeMusic),
		{ GetPercentageScreenWidth(50) - MeasureText(TextFormat("%i", volumeMusic) , 35) / 2, GetPercentageScreenHeight(32) },
		35, GetPercentageScreenWidth(0.5), RED);

	buttonUpVolumeMusicOptions->DrawButton();
	buttonDownVolumeMusicOptions->DrawButton();

	//sfx
	int volumeSFX = static_cast<int>(getVolumeSFX() * 10);

	DrawTextEx(fontTitles, "SFX", { GetPercentageScreenWidth(50) - MeasureText("SFX", 35) / 2, GetPercentageScreenHeight(39) },
		35, GetPercentageScreenWidth(0.5), BLACK);


	DrawTexturePro(textureOptionsButton,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(8) / 2), GetPercentageScreenHeight(45),
			GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(fontTitles, TextFormat("%i", volumeSFX),
		{ GetPercentageScreenWidth(50) - MeasureText(TextFormat("%i", volumeSFX) , 35) / 2, GetPercentageScreenHeight(47) },
		35, GetPercentageScreenWidth(0.5), RED);

	buttonUpVolumeSFXOptions->DrawButton();
	buttonDownVolumeSFXOptions->DrawButton();
}

void CreateButtonsOptions()
{
	buttonUpVolumeMusicOptions = new Buttons(
		{ GetPercentageScreenWidth(58), GetPercentageScreenHeight(30),
		GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		RED, "+", 35);

	buttonDownVolumeMusicOptions = new Buttons(
		{ GetPercentageScreenWidth(34), GetPercentageScreenHeight(30),
		GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		RED, "-", 35);

	buttonUpVolumeSFXOptions = new Buttons(
		{ GetPercentageScreenWidth(58), GetPercentageScreenHeight(45),
		GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		RED, "+", 35);

	buttonDownVolumeSFXOptions = new Buttons(
		{ GetPercentageScreenWidth(34), GetPercentageScreenHeight(45),
		GetPercentageScreenWidth(8), GetPercentageScreenHeight(8) },
		RED, "-", 35);

	buttonExitOptions = new Buttons(
		{ GetPercentageScreenWidth(85), GetPercentageScreenHeight(85),
		GetPercentageScreenWidth(10), GetPercentageScreenHeight(10) },
		RED, "Exit", 30);
}

void LoadResourcesOptions()
{
	textureOptionsBackground = LoadTexture("res/textures/simpleBackground.png");
	textureOptionsButton = LoadTexture("res/textures/button.png");

	fontTitles = LoadFont("res/fonts/DS-DIGI.TTF");

	OptionsRosurcesLoaded = true;
}

void UnloadResourcesOptions()
{
	UnloadTexture(textureOptionsBackground);
	UnloadTexture(textureOptionsButton);

	OptionsRosurcesLoaded = false;
}