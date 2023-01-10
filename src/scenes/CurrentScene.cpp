#include "CurrentScene.h"

void InitGame()
{
	int DefaultScreenWidth = 800;
	int DefaultScreenHeight = 800;

	bool IsRunning = true;

	InitWindow(DefaultScreenWidth, DefaultScreenHeight, "WHERE IS MY TIME!?");
	SetExitKey(NULL);

	gamescene = GameScene::GameLoop;

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

	if (IsKeyPressed(KEY_ESCAPE))
	{
		gamescene = GameScene::Exit;
	}
		

		break;
	case GameScene::GameLoop:
		GameLoopScene();

		break;
	case GameScene::Rules:
		

		break;
	case GameScene::Credits:


		break;
	case GameScene::Exit:
		IsRunning = false;
		break;

	default:
		break;
	}
}