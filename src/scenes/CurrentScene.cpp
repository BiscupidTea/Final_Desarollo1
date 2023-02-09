#include "CurrentScene.h"

GameScene gameScene;

void InitGame()
{
	int DefaultScreenWidth = 800;
	int DefaultScreenHeight = 800;

	bool IsRunning = true;

	InitWindow(DefaultScreenWidth, DefaultScreenHeight, "WHERE IS MY TIME!?");
	SetExitKey(NULL);
	HideCursor();

	setGameScene(GameScene::Menu);

	while (!WindowShouldClose() && IsRunning)
	{
		ScreenScene(IsRunning);
	}

	UnloadResources();

	CloseWindow();
}

void ScreenScene(bool& IsRunning) {
	switch (gameScene)
	{
	case GameScene::Menu:
		MenuScene();
		break;

	case GameScene::GameLoop:
		GameLoopScene();
		break;

	case GameScene::Rules:
		setGameScene(GameScene::Menu);
		break;

	case GameScene::Options:
		setGameScene(GameScene::Menu);
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
}

void UnloadResources()
{
	UnloadResourcesGame();
	UnloadResourcesMenu();
}