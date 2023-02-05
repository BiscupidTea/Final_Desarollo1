#include "Game.h"

static const int maxObstacles = 12;
static const int maxBullets = 5;
static int objectsToMove;
static float objectFrameDetector;
static bool firtRun;
static bool isGamePause = false;
static bool aliveButtons = false;
static bool cheats = false;
static int highScore = 0;
static int totalDistance = 0;
static bool isResoucesLoad = false;

static Texture2D textureShieldItem;
static Texture2D texturePlayer;

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
PowerUp* itemPowerUp;
Timer* deathTimer;
Obstacle* arrayObstacle[maxObstacles];

void InitGameLoop()
{
	LoadResources();

	if (LoadStorageValue(0) != 0)
	{
		highScore = LoadStorageValue(0);
	}
	else
	{
		highScore = 0;
	}

	if (LoadStorageValue(1) != 0)
	{
		totalDistance = LoadStorageValue(1);
	}
	else
	{
		totalDistance = 0;
	}

	player1 = new Player({ 0, 0 }, { 0, 50 }, 0, 0, true, texturePlayer);

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i] = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60);
	}

	isGamePause = false;

	objectsToMove = 0;
	objectFrameDetector = static_cast<float>(GetScreenWidth());
	firtRun = true;

	itemTimer = new TimerItem(
		{ static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(25) },
		{ 150 , 400 }, 15, 15, 10, GetPercentageScreenHeight(42.5), 5);

	itemPowerUp = new PowerUp(
		{ 0, 0 }, { 150 , 0 }, 15, 15, 5, textureShieldItem);
	itemPowerUp->ResetRandPosition();

	deathTimer = new Timer(30);

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

	DrawText("0.5", GetScreenWidth() - MeasureText("0.5", 40), GetScreenHeight() - MeasureText("0.5", 20), 20, WHITE);
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

	arrayObstacle[objectsToMove]->SetDestroyed(false);
	arrayObstacle[objectsToMove + 1]->SetDestroyed(false);
	arrayObstacle[objectsToMove + 2]->SetDestroyed(false);
	arrayObstacle[objectsToMove + 3]->SetDestroyed(false);

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
			if (player1->CheckColition(arrayObstacle[i]->GetPosition(),
				arrayObstacle[i]->GetWidth(), arrayObstacle[i]->GetHeight())
				&& !arrayObstacle[i]->IsDestroyed())
			{
				if (itemPowerUp->IsPicked())
				{
					itemPowerUp->SetPicked(false);
					arrayObstacle[i]->SetDestroyed(true);
				}
				else
				{
					KillPlayer();
				}
			}
		}
	}

	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsShootedNow())
		{
			for (int j = 0; j < maxObstacles; j++)
			{
				if (player1->arrayBullets[i]->CheckColition(arrayObstacle[j]->GetPosition(),
					arrayObstacle[j]->GetWidth(), arrayObstacle[j]->GetHeight()))
				{
					arrayObstacle[j]->SetDestroyed(true);
				}
			}
		}
	}

	if (player1->CheckColition(itemTimer->GetPosition(), itemTimer->GetWidth(), itemTimer->GetHeight()))
	{
		deathTimer->AddTime(itemTimer->GettimeAdd());
		itemTimer->ResetRandPosition();
		itemTimer->holdTimer->ResetTime();
	}

	if (!itemPowerUp->IsPicked())
	{
		if (player1->CheckColition(itemPowerUp->GetPosition(), itemPowerUp->GetWidth(), itemPowerUp->GetHeight()))
		{
			itemPowerUp->ResetRandPosition();
			itemPowerUp->spawnItem->ResetTime();
			itemPowerUp->SetPicked(true);
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

		buttonRestart = new Buttons(
			{ GetPercentageScreenWidth(35) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(70),
			GetPercentageScreenWidth(25), GetPercentageScreenHeight(10) },
			RED, "Restart", 25);

		buttonBackToMenu = new Buttons(
			{ GetPercentageScreenWidth(65) - (GetPercentageScreenWidth(25) / 2), GetPercentageScreenHeight(70),
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

	//item logic
	if (itemTimer->holdTimer->GetTimer() <= 0)
	{
		itemTimer->UpdateItem();

		if (itemTimer->OutOfLimits())
		{
			itemTimer->ResetRandPosition();
		}
	}
	else
	{
		itemTimer->holdTimer->UpdateTimer();
	}

	if (itemPowerUp->spawnItem->GetTimer() <= 0)
	{
		itemPowerUp->UpdateItem();

		if (itemPowerUp->OutOfLimits())
		{
			itemPowerUp->ResetRandPosition();
		}
	}
	else
	{
		itemPowerUp->spawnItem->UpdateTimer();
	}

	//obstacles logic
	ResetObstacleOutOfLimits();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i]->Movement();
	}

	//deathTimer logic
	if (!cheats)
	{
		if (deathTimer->GetIsTimeEnd())
		{
			KillPlayer();
		}
		else
		{
			deathTimer->UpdateTimer();
		}
	}

	//bullets logic
	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsShootedNow())
		{
			player1->arrayBullets[i]->UpdateBullet();
		}

		player1->arrayBullets[i]->OutOfLimits();
	}

	CheckColitions();
}

void GameplayDraw()
{
	ClearBackground(BLACK);

	if (itemPowerUp->IsPicked())
	{
		DrawCircle(
			static_cast<int>(player1->GetX() + player1->GetWidth() / 2),
			static_cast<int>(player1->GetY() + player1->GetHeight() / 2),
			static_cast<float>(player1->GetWidth()), RED);
	}

	player1->Draw();


	//draw items
	itemTimer->Draw();
	itemPowerUp->Draw();

	//draw obstacles
	for (int i = 0; i < maxObstacles; i++)
	{
		if (!arrayObstacle[i]->IsDestroyed())
		{
			arrayObstacle[i]->Draw();
		}
		else
		{
			DrawRectangleLines(
				static_cast<int>(arrayObstacle[i]->GetX()),
				static_cast<int>(arrayObstacle[i]->GetY()),
				arrayObstacle[i]->GetWidth(),
				arrayObstacle[i]->GetHeight(),
				RED
			);
		}
	}

	//draw bullets
	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsShootedNow())
		{
			player1->arrayBullets[i]->Draw();
		}
	}

	DrawRectangle(0,
		static_cast<int>(GetPercentageScreenHeight(85.0f)),
		GetScreenWidth(),
		static_cast<int>(GetPercentageScreenHeight(15.0f)),
		GREEN
	);

	DrawHud();
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

	if (static_cast<int>(player1->GetDistanceMade()) > highScore)
	{
		highScore = static_cast<int>(player1->GetDistanceMade());
		SaveStorageValue(0, highScore);
	}

	if (buttonBackToMenu->IsButtonPressed())
	{
		UnloadResources();
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

	float high1 = 35;
	float high2 = 45;
	float high3 = 55;

	//total distance made
	DrawText("Distance Runned :",
		static_cast<int>(GetPercentageScreenWidth(20)),
		static_cast<int>(GetPercentageScreenHeight(high1)), 30, RED);

	DrawText(
		TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())),
		static_cast<int>(GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 30) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high1)),
		30, RED
	);

	DrawText(
		"m",
		static_cast<int>(GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 40) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high1)),
		30, RED
	);

	//high score
	DrawText("High score :",
		static_cast<int>(GetPercentageScreenWidth(20)),
		static_cast<int>(GetPercentageScreenHeight(high2)), 30, RED);

	DrawText(
		TextFormat("%01i", highScore),
		static_cast<int>(GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", highScore), 30) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high2)),
		30, RED
	);

	DrawText(
		"m",
		static_cast<int>(GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", highScore), 40) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high2)),
		30, RED
	);

	//total distance save distance
	DrawText("Total Distance :",
		static_cast<int>(GetPercentageScreenWidth(20)),
		static_cast<int>(GetPercentageScreenHeight(high3)), 30, RED);

	DrawText(
		TextFormat("%01i", totalDistance),
		static_cast<int>(GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", totalDistance), 30) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high3)),
		30, RED
	);

	DrawText(
		"m",
		static_cast<int>(GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", totalDistance), 40) / 2)),
		static_cast<int>(GetPercentageScreenHeight(high3)),
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

void DrawHud()
{
	//timer
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
		static_cast<int>(GetPercentageScreenHeight(6) + player1->arrayBullets[0]->GetHeight()),
		player1->arrayBullets[0]->GetWidth(), player1->arrayBullets[0]->GetHeight(), BROWN
	);

	DrawText(
		" = ",
		static_cast<int>(GetPercentageScreenWidth(3) + player1->arrayBullets[0]->GetWidth()),
		static_cast<int>(GetPercentageScreenHeight(6) + player1->arrayBullets[0]->GetHeight()),
		30, WHITE
	);

	int bulletsPicked = 0;
	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsPickedNow())
		{
			bulletsPicked += 1;
		}
	}

	DrawText(
		TextFormat("%01i", static_cast<int>(bulletsPicked)),
		static_cast<int>(GetPercentageScreenWidth(3) + player1->arrayBullets[0]->GetWidth() + (MeasureText(" = ", 30))),
		static_cast<int>(GetPercentageScreenHeight(6) + player1->arrayBullets[0]->GetHeight()),
		30, WHITE
	);
}

void KillPlayer()
{
	player1->SetIsAlive(false);
	totalDistance += static_cast<int>(player1->GetDistanceMade());
	SaveStorageValue(1, totalDistance);
}

void LoadResources()
{
	if (!isResoucesLoad)
	{
		textureShieldItem = LoadTexture("res/textures/shield-item.png");
		texturePlayer = LoadTexture("res/textures/PlayerTexture.png");
	}

	isResoucesLoad = true;
}

void UnloadResources()
{
	UnloadTexture(textureShieldItem);
	UnloadTexture(texturePlayer);
}