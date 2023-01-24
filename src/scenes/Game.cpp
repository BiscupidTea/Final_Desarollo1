#include "Game.h"

static const int maxObstacles = 12;
static int objectsToMove;
static float objectFrameDetector;
static bool firtRun;
static bool isGamePause = false;
static bool aliveButtons = false;

Buttons* buttonResume;
Buttons* buttonRestart;
Buttons* buttonBackToMenu;
Buttons* buttonUpVolume;
Buttons* buttonDownVolume;

enum class ObjectsPatterns
{
	StairFloor = 1,
	StariCeiling,
	WallFloor,
	WallCeiling,
	MountainFloor,
	MountainCeiling,
	MidLine,
};

Player* player1;
Timer* deathTimer;
Obstacle* arrayobstacle[maxObstacles];

void InitGameLoop()
{
	player1 = new Player({ 0, 0 }, { 0, 50 }, 40, 60, 0, 0, true);

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayobstacle[i] = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60);
	}

	isGamePause = false;

	objectsToMove = 0;
	objectFrameDetector = static_cast<float>(GetScreenWidth());
	firtRun = true;

	deathTimer = new Timer(30);

	CreateGameButtons();
	InitPlayer();
	ResetObstacle();
}

void GameLoopScene()
{
	UpdateGame();

	DrawGame();
}

void DrawGame()
{
	BeginDrawing();

	GameplayDraw();

	if (isGamePause && player1->IsAlive())
	{
		PauseDraw();
	}

	if (!player1->IsAlive())
	{
		DeathScreenDraw();
	}

	DrawText("0.3", GetScreenWidth() - MeasureText("0.3", 40), GetScreenHeight() - MeasureText("0.3", 20), 20, WHITE);
	EndDrawing();
}

void UpdateGame()
{
	player1->Input(isGamePause);

	if (!isGamePause && player1->IsAlive())
	{
		GameplayUpdate();
	}
	else if (!player1->IsAlive())
	{
		DeathScreenUpdate();
	}
	else
	{
		PauseUpdate();
	}
}

void InitPlayer()
{
	player1->SetPosition({ GetPercentageScreenWidth(10.0f),GetPercentageScreenHeight(85.0f) - player1->GetHeight() });
}

void ResetObstacle()
{
	//wallfloor
	arrayobstacle[0]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(85) - arrayobstacle[objectsToMove]->GetHeight() });
	arrayobstacle[1]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(75) - arrayobstacle[objectsToMove]->GetHeight() });
	arrayobstacle[2]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(65) - arrayobstacle[objectsToMove]->GetHeight() });
	arrayobstacle[3]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(55) - arrayobstacle[objectsToMove]->GetHeight() });

	//wallceiling
	arrayobstacle[4]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), 0 });
	arrayobstacle[5]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(10) });
	arrayobstacle[6]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(20) });
	arrayobstacle[7]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(30) });

	//midline
	arrayobstacle[8]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(30), GetPercentageScreenHeight(85) / 2 });
	arrayobstacle[9]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(85) / 2 });
	arrayobstacle[10]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(85) / 2 });
	arrayobstacle[11]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) / 2 });
}

void ResetObstacleOutOfLimits()
{
	objectFrameDetector -= arrayobstacle[0]->getVelocityX() * GetFrameTime();

	if (firtRun)
	{
		firtRun = false;
		objectFrameDetector = static_cast<float>(GetScreenWidth() * 2);
	}
	else
	{
		if (objectFrameDetector <= 0)
		{
			cout << "The next position is : ";
			SetObstaclePattern();
			objectFrameDetector = static_cast<float>(GetScreenWidth());
		}
	}

}

void SetObstaclePattern()
{
	ObjectsPatterns randomPattern;

	randomPattern = ObjectsPatterns::WallFloor;

	randomPattern = static_cast<ObjectsPatterns>(GetRandomValue(1, 7));

	switch (randomPattern)
	{
	case ObjectsPatterns::StairFloor:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), GetPercentageScreenHeight(85) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(40)), GetPercentageScreenHeight(75) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(50)), GetPercentageScreenHeight(65) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(60)), GetPercentageScreenHeight(55) - arrayobstacle[objectsToMove]->GetHeight() });
		cout << "StairFloor" << endl;
		break;
	case ObjectsPatterns::StariCeiling:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(40)), GetPercentageScreenHeight(10) });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(50)), GetPercentageScreenHeight(20) });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(60)), GetPercentageScreenHeight(30) });
		cout << "StariCeiling" << endl;
		break;
	case ObjectsPatterns::WallFloor:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(85) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(75) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(65) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(55) - arrayobstacle[objectsToMove]->GetHeight() });
		cout << "WallFloor" << endl;
		break;
	case ObjectsPatterns::WallCeiling:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), 0 });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(10) });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(20) });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(30) });
		cout << "WallCeiling" << endl;
		break;
	case ObjectsPatterns::MountainFloor:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), GetPercentageScreenHeight(85) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(75) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(75) - arrayobstacle[objectsToMove]->GetHeight() });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) - arrayobstacle[objectsToMove]->GetHeight() });
		cout << "MountainFloor" << endl;
		break;
	case ObjectsPatterns::MountainCeiling:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(10) });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(10) });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), 0 });
		cout << "MountainCeiling" << endl;
		break;
	case ObjectsPatterns::MidLine:
		arrayobstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(30), GetPercentageScreenHeight(85) / 2 });
		arrayobstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(85) / 2 });
		arrayobstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(85) / 2 });
		arrayobstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) / 2 });
		cout << "MidLine" << endl;
		break;
	default:
		break;
	}

	objectsToMove += 4;

	if (objectsToMove >= 12)
	{
		objectsToMove = 0;
	}

	cout << objectsToMove << endl;
}

void CheckColitions()
{
	for (int i = 0; i < maxObstacles; i++)
	{
		if (player1->CheckColition(arrayobstacle[i]->GetPosition(), arrayobstacle[i]->GetWidth(), arrayobstacle[i]->GetHeight()))
		{
			player1->SetIsAlive(false);
		}
	}
}

void CreateGameButtons()
{
	if (player1->IsAlive())
	{
		buttonResume = new Buttons(
			{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(30),
			GetPercentageScreenWidth(25), GetPercentageScreenHeight(10) },
			RED, "Resume", 25);

		buttonRestart = new Buttons(
			{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(55),
			GetPercentageScreenWidth(25), GetPercentageScreenHeight(10) },
			RED, "Restart", 25);

		buttonBackToMenu = new Buttons(
			{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(70),
			GetPercentageScreenWidth(25), GetPercentageScreenHeight(10) },
			RED, "Back to Menu", 25);

		buttonDownVolume = new Buttons(
			{ GetPercentageScreenWidth(40) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(50),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
			RED, "-", 25);

		buttonUpVolume = new Buttons(
			{ GetPercentageScreenWidth(60) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(50),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
			RED, "+", 25);
	}
	else
	{

		buttonBackToMenu = new Buttons(
			{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(70),
			GetPercentageScreenWidth(25), GetPercentageScreenHeight(10) },
			RED, "Back to Menu", 25);
	}

}

void GameplayUpdate()
{
	player1->IsPlayerGround();
	player1->Movement();

	ResetObstacleOutOfLimits();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayobstacle[i]->Movement();
	}


	if (deathTimer->GetIsTimeEnd())
	{
		player1->SetIsAlive(false);
	}
	else
	{
		deathTimer->UpdateTimer();
		cout << deathTimer->GetTimer() << endl;
	}

	CheckColitions();
}

void GameplayDraw()
{
	ClearBackground(BLACK);
	player1->Draw();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayobstacle[i]->Draw();
	}

	DrawRectangle(0,
		static_cast<int>(GetPercentageScreenHeight(85.0f)),
		GetScreenWidth(),
		static_cast<int>(GetPercentageScreenHeight(15.0f)),
		GREEN
	);

	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(9) / 2)),
		static_cast<int>(GetPercentageScreenHeight(3)),
		static_cast<int>(GetPercentageScreenWidth(9)),
		static_cast<int>(GetPercentageScreenHeight(6)),
		WHITE
	);

	if (deathTimer->GetTimer() > 20)
	{
		DrawText(
			TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("00", 50) / 2)),
			static_cast<int>(GetPercentageScreenHeight(3)),
			50, GREEN);
	}
	else if (deathTimer->GetTimer() > 10)
	{
		DrawText(
			TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("10", 50) / 2)),
			static_cast<int>(GetPercentageScreenHeight(3)),
			50, GREEN);
	}
	else
	{
		DrawText(
			TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			static_cast<int>(GetPercentageScreenWidth(50) - (MeasureText("0", 50) / 2)),
			static_cast<int>(GetPercentageScreenHeight(3)),
			50, GREEN);
	}

}

void PauseUpdate()
{
	if (buttonResume->IsButtonPressed())
	{
		isGamePause = false;
	}

	if (buttonBackToMenu->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
	}

	//buttonUpVolume->IsButtonPressed();
	//buttonDownVolume->IsButtonPressed();
}

void PauseDraw()
{
	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(15)),
		static_cast<int>(GetPercentageScreenHeight(15)),
		static_cast<int>(GetPercentageScreenWidth(70)),
		static_cast<int>(GetPercentageScreenHeight(70)),
		WHITE
	);

	buttonResume->DrawButton();
	buttonBackToMenu->DrawButton();
	buttonUpVolume->DrawButton();
	buttonDownVolume->DrawButton();
}

void DeathScreenUpdate()
{
	if (!aliveButtons)
	{
		CreateGameButtons();
	}

	if (buttonBackToMenu->IsButtonPressed())
	{
		setGameScene(GameScene::Menu);
	}

	if (buttonRestart->IsButtonPressed())
	{
		InitGameLoop();
	}
}

void DeathScreenDraw()
{
	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(15)),
		static_cast<int>(GetPercentageScreenHeight(15)),
		static_cast<int>(GetPercentageScreenWidth(70)),
		static_cast<int>(GetPercentageScreenHeight(70)),
		WHITE
	);

	DrawText("Game Over",
		static_cast<int>(GetPercentageScreenWidth(50)) - (MeasureText("Game Over", 40) / 2),
		static_cast<int>(GetPercentageScreenHeight(20)), 40, RED);

	buttonRestart->DrawButton();
	buttonBackToMenu->DrawButton();
}