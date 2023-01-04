#include "CurrentScene.h"

void InitGame()
{
	int DefaultScreenWidth = 800;
	int DefaultScreenHeight = 800;

	bool IsRunning = true;

	InitWindow(DefaultScreenWidth, DefaultScreenHeight, "WHERE IS MY TIME!?");
	SetExitKey(KEY_NULL);

	while (!WindowShouldClose())
	{
		ClearBackground(BLACK);
		ScreenScene(IsRunning);
	}

	CloseWindow();
}

void ScreenScene(bool& IsRunning) {
	switch (gamescene)
	{
	case GameScene::Menu:
		SetExitKey(KEY_ESCAPE);
		

		break;
	case GameScene::GameLoop:
		SetExitKey(NULL);
		

		break;
	case GameScene::Rules:
		SetExitKey(NULL);
		

		break;
	case GameScene::Credits:
		SetExitKey(NULL);
		

		break;
	case GameScene::Exit:
		IsRunning = false;
		break;
	default:
		break;
	}
}