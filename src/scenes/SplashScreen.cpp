#include "SplashScreen.h"

#include "raylib.h"
#include "tools/tools.h"
#include "tools/Cursor.h"
#include "tools/Timer.h"

#include "scenes/SceneSetter.h"

namespace Game
{
	static bool SplashScreenRosurcesLoaded = false;
	static bool firstPhase = true;
	static Color SplashScreenColor;
	static int timesEndTimer = 0;

	Texture2D textureSplashScreen;

	Timer* timerSplashScreen;

	void SplashScreenScene()
	{

		if (!SplashScreenRosurcesLoaded)
		{
			LoadTextureSplashScreen();
		}

		UpdateSplashScreen();

		DrawSplashScreen();
	}

	void UpdateSplashScreen()
	{
		timerSplashScreen->UpdateTimer();

		if (timerSplashScreen->GetIsTimeEnd())
		{
			if (firstPhase)
			{
				SplashScreenColor.a -= 1;

				if (SplashScreenColor.a == 0)
				{
					firstPhase = false;
				}
			}
			else
			{
				SplashScreenColor.a += 1;

				if (SplashScreenColor.a == 255)
				{
					setGameScene(GameScene::Menu);
				}
			}

			timerSplashScreen->ResetTime();
			timesEndTimer++;
		}
	}

	void DrawSplashScreen()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawTexturePro(textureSplashScreen,
			{ 0,0,128,128 },
			{ 0,0, static_cast<float>(800) , static_cast<float>(800) },
			{}, 0, WHITE);

		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SplashScreenColor);

		EndDrawing();
	}

	void LoadTextureSplashScreen()
	{
		textureSplashScreen = LoadTexture("res/textures/splashscreen.png");

		timerSplashScreen = new Timer(0.01f);

		SplashScreenColor = { 0,0,0,255 };

		SplashScreenRosurcesLoaded = true;
	}
}