#include "Game.h"

static const int maxObstacles = 12;
static const int maxBullets = 5;
static int objectsToMove;
static float objectFrameDetector;
static bool firtRun;
static bool isGamePause = false;
static bool aliveButtons = false;
static bool cheats = false;

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
TimerItem* itemTimer;
Timer* deathTimer;
Timer* spawnItemTimer;
Obstacle* arrayObstacle[maxObstacles];
Bullet* arrayBullets[maxBullets];

void InitGameLoop()
{
	player1 = new Player({ 0, 0 }, { 0, 50 }, 40, 60, 0, 0, true);

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i] = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60);
	}

	for (int i = 0; i < maxBullets; i++)
	{
		arrayBullets[i] = new Bullet({ -500, -500 }, { 400, 0 }, 20, 20, true);
	}

	isGamePause = false;

	objectsToMove = 0;
	objectFrameDetector = static_cast<float>(GetScreenWidth());
	firtRun = true;

	itemTimer = new TimerItem(
		{ static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(25) },
		{ 150 , 400 }, 15, 15, 10,
		GetPercentageScreenHeight(42.5));

	deathTimer = new Timer(30);
	spawnItemTimer = new Timer(5);

	itemTimer->ResetRandPosition();
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

	DrawText("0.4", GetScreenWidth() - MeasureText("0.4", 40), GetScreenHeight() - MeasureText("0.4", 20), 20, WHITE);
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
	arrayObstacle[0]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
	arrayObstacle[1]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
	arrayObstacle[2]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(65) - arrayObstacle[objectsToMove]->GetHeight() });
	arrayObstacle[3]->SetPosition({ static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2), GetPercentageScreenHeight(55) - arrayObstacle[objectsToMove]->GetHeight() });

	//wallceiling
	arrayObstacle[4]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), 0 });
	arrayObstacle[5]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(10) });
	arrayObstacle[6]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(20) });
	arrayObstacle[7]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(30) });

	//midline
	arrayObstacle[8]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(30), GetPercentageScreenHeight(85) / 2 });
	arrayObstacle[9]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(85) / 2 });
	arrayObstacle[10]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(85) / 2 });
	arrayObstacle[11]->SetPosition({ static_cast<float>(GetScreenWidth() * 3) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) / 2 });
}

void ResetObstacleOutOfLimits()
{
	objectFrameDetector -= arrayObstacle[0]->getVelocityX() * GetFrameTime();

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
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(40)), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(50)), GetPercentageScreenHeight(65) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(60)), GetPercentageScreenHeight(55) - arrayObstacle[objectsToMove]->GetHeight() });
		cout << "StairFloor" << endl;
		break;
	case ObjectsPatterns::StariCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(40)), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(50)), GetPercentageScreenHeight(20) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(60)), GetPercentageScreenHeight(30) });
		cout << "StariCeiling" << endl;
		break;
	case ObjectsPatterns::WallFloor:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(65) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(55) - arrayObstacle[objectsToMove]->GetHeight() });
		cout << "WallFloor" << endl;
		break;
	case ObjectsPatterns::WallCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(20) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(30) });
		cout << "WallCeiling" << endl;
		break;
	case ObjectsPatterns::MountainFloor:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		cout << "MountainFloor" << endl;
		break;
	case ObjectsPatterns::MountainCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), 0 });
		cout << "MountainCeiling" << endl;
		break;
	case ObjectsPatterns::MidLine:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(30), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) / 2 });
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
	if (!cheats)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			if (player1->CheckColition(arrayObstacle[i]->GetPosition(), arrayObstacle[i]->GetWidth(), arrayObstacle[i]->GetHeight()))
			{
				player1->SetIsAlive(false);
			}
		}
	}

	if (player1->CheckColition(itemTimer->GetPosition(), itemTimer->GetWidth(), itemTimer->GetHeight()))
	{
		deathTimer->AddTime(itemTimer->GettimeAdd());
		itemTimer->ResetRandPosition();
		spawnItemTimer->SetTime(5);
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
	AccelerateGame();

	player1->IsPlayerGround();
	player1->Movement();
	player1->AddDistanceMade(arrayObstacle[0]->getVelocityX() / 100 * GetFrameTime());

	if (IsKeyPressed(KEY_F))
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (arrayBullets[i]->IsPickedNow())
			{
				arrayBullets[i]->ShootBullet(player1->GetPosition());
				cout << "fire" << endl;
				break;
			}
		}
	}

	if (spawnItemTimer->GetTimer() <= 0)
	{
		itemTimer->UpdateItem();

		if (itemTimer->GetX() - itemTimer->GetWidth() < 0)
		{
			spawnItemTimer->SetTime(5);
			itemTimer->ResetRandPosition();
		}
	}
	else
	{
		spawnItemTimer->UpdateTimer();
	}

	ResetObstacleOutOfLimits();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i]->Movement();
	}

	if (!cheats)
	{
		if (deathTimer->GetIsTimeEnd())
		{
			player1->SetIsAlive(false);
		}
		else
		{
			deathTimer->UpdateTimer();
		}
	}

	for (int i = 0; i < maxBullets; i++)
	{
		if (arrayBullets[i]->IsShootedNow())
		{
			arrayBullets[i]->UpdateBullet();
		}

		arrayBullets[i]->OutOfLimits();
	}

	CheckColitions();
}

void GameplayDraw()
{
	ClearBackground(BLACK);
	player1->Draw();
	itemTimer->Draw();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i]->Draw();
	}

	for (int i = 0; i < maxBullets; i++)
	{
		if (arrayBullets[i]->IsShootedNow())
		{
			arrayBullets[i]->Draw();
		}
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

	//timer
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

	//meters
	DrawText(
		TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())),
		static_cast<int>(GetPercentageScreenWidth(3)),
		static_cast<int>(GetPercentageScreenHeight(3)),
		30, WHITE
	);

	DrawText(
		"m",
		static_cast<int>(GetPercentageScreenWidth(4) + (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 30))),
		static_cast<int>(GetPercentageScreenHeight(3)),
		30, WHITE
	);

	//bullets
	DrawRectangle(
		static_cast<int>(GetPercentageScreenWidth(3)),
		static_cast<int>(GetPercentageScreenHeight(6) + arrayBullets[0]->GetHeight()),
		arrayBullets[0]->GetWidth(), arrayBullets[0]->GetHeight(), BROWN
	);

	DrawText(
		" = ",
		static_cast<int>(GetPercentageScreenWidth(3) + arrayBullets[0]->GetWidth()),
		static_cast<int>(GetPercentageScreenHeight(6) + arrayBullets[0]->GetHeight()),
		30, WHITE
	);

	int bulletsPicked = 0;
	for (int i = 0; i < maxBullets; i++)
	{
		if (arrayBullets[i]->IsPickedNow())
		{
			bulletsPicked += 1;
		}
	}

	DrawText(
		TextFormat("%01i", static_cast<int>(bulletsPicked)),
		static_cast<int>(GetPercentageScreenWidth(3) + arrayBullets[0]->GetWidth() + (MeasureText(" = ", 30))),
		static_cast<int>(GetPercentageScreenHeight(6) + arrayBullets[0]->GetHeight()),
		30, WHITE
	);

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

	DrawText("Total Distance :",
		static_cast<int>(GetPercentageScreenWidth(50)) - (MeasureText("Total Distance :", 30) / 2),
		static_cast<int>(GetPercentageScreenHeight(30)), 30, RED);

	DrawText(
		TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())),
		static_cast<int>(GetPercentageScreenWidth(50) - ((MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 30)) / 2)),
		static_cast<int>(GetPercentageScreenHeight(40)),
		30, RED
	);

	DrawText(
		"m",
		static_cast<int>(GetPercentageScreenWidth(51) + (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 30) / 2)),
		static_cast<int>(GetPercentageScreenHeight(40)),
		30, RED
	);

	buttonRestart->DrawButton();
	buttonBackToMenu->DrawButton();
}

void AccelerateGame()
{
	if (player1->GetDistanceMade() >= 100)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			arrayObstacle[i]->setVelocityX(400);
		}
	}

	if (player1->GetDistanceMade() >= 300)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			arrayObstacle[i]->setVelocityX(500);
		}
	}

	if (player1->GetDistanceMade() >= 600)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			arrayObstacle[i]->setVelocityX(600);
		}
	}

	if (player1->GetDistanceMade() >= 800)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			arrayObstacle[i]->setVelocityX(700);
		}
	}

	if (player1->GetDistanceMade() >= 1000)
	{
		for (int i = 0; i < maxObstacles; i++)
		{
			arrayObstacle[i]->setVelocityX(800);
		}
	}
}