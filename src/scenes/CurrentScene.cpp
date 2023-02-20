#include "CurrentScene.h"

#include "raylib.h"

#include "SceneSetter.h"
#include "scenes/SplashScreen.h"
#include "scenes/Menu.h"
#include "scenes/Game.h"
#include "scenes/Rules.h"
#include "scenes/Options.h"
#include "scenes/Credits.h"

using namespace Game;

GameScene gameScene;

Music GameMusic1;
Music MenuMusic1;

void InitGame()
{
	int DefaultScreenWidth = 800;
	int DefaultScreenHeight = 800;

	bool IsRunning = true;

	InitWindow(DefaultScreenWidth, DefaultScreenHeight, "WHERE IS MY TIME!?");
	InitAudioDevice();
	setVolumeMusic(0.5);
	setVolumeSFX(0.5);

	SetExitKey(NULL);
	HideCursor();

	GameMusic1 = LoadMusicStream("res/sounds/music/GameMusic1.wav");
	MenuMusic1 = LoadMusicStream("res/sounds/music/MenuMusic1.wav");

	setGameScene(GameScene::SplashScreen);

	while (!WindowShouldClose() && IsRunning)
	{
		ScreenScene(IsRunning);
	}

	UnloadResources();

	CloseAudioDevice();
	CloseWindow();
}

void ScreenScene(bool& IsRunning) {
	switch (gameScene)
	{
	case GameScene::SplashScreen:
		SplashScreenScene();
		break;

	case GameScene::Menu:
		MenuScene();
		break;

	case GameScene::GameLoop:
		GameLoopScene();
		break;

	case GameScene::Rules:
		RulesScene();
		break;

	case GameScene::Options:
		OptionsScene();
		break;

	case GameScene::Credits:
		CreditsScene();
		break;

	case GameScene::Exit:
		IsRunning = false;
		break;

	default:
		break;
	}

	SetMusicVolume(MenuMusic1, getVolumeMusic());
	SetMusicVolume(GameMusic1, getVolumeMusic());

	if (gameScene == GameScene::GameLoop)
	{
		StopMusicStream(MenuMusic1);

		if (!IsMusicStreamPlaying(GameMusic1))
		{
			PlayMusicStream(GameMusic1);
		}
		else
		{
			UpdateMusicStream(GameMusic1);
		}
	}
	else
	{
		StopMusicStream(GameMusic1);

		if (!IsMusicStreamPlaying(MenuMusic1))
		{
			PlayMusicStream(MenuMusic1);
		}
		else
		{
			UpdateMusicStream(MenuMusic1);
		}
	}

}

void UnloadResources()
{
	UnloadResourcesGame();
	UnloadResourcesMenu();
}