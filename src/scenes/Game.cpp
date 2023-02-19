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
static bool isButtonsCreated = false;

Texture2D textureMouse;
Texture2D textureShieldItem;
Texture2D textureShieldPicked;
Texture2D texturePlayer;
Texture2D textureTimer;
Texture2D textureObstacle;
Texture2D textureBullet;
Texture2D textureExplotion;
Texture2D textureClock;
Texture2D textureBlock;
Texture2D textureFloor;
Texture2D textureWall1;
Texture2D textureWall2;
Texture2D textureWindow1;
Texture2D texturePauseBack;
Texture2D textureDeathScreen;

Sound soundPlayerJump;
Sound soundPlayerFly;
Sound soundPlayerShoot;
Sound soundShieldActive;
Sound soundItemPicked;
Sound soundExplotion;

Font gameFont;

Buttons* buttonResume;
Buttons* buttonRestart;
Buttons* buttonBackToMenu;

Buttons* buttonUpVolumeMusic;
Buttons* buttonDownVolumeMusic;
Buttons* buttonUpVolumeSFX;
Buttons* buttonDownVolumeSFX;

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

Paralax* paralax1;
Player* player1;
TimerItem* itemTimer;
PowerUp* itemPowerUp;
Timer* deathTimer;
Obstacle* arrayObstacle[maxObstacles];

void InitGameLoop()
{
	LoadResourcesGame();

	isButtonsCreated = false;

	HideCursor();

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

	player1 = new Player({ 0, 0 }, { 0, 50 }, 0, 0, true, texturePlayer, textureBullet);

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i] = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60, textureObstacle, textureExplotion);
	}

	paralax1 = new Paralax(300, textureFloor, textureWall1, textureWall2, textureWindow1);

	isGamePause = false;

	objectsToMove = 0;
	objectFrameDetector = static_cast<float>(GetScreenWidth());
	firtRun = true;

	itemTimer = new TimerItem(
		{ static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(25) },
		{ 150 , 400 }, 15, 15, 10, GetPercentageScreenHeight(42.5), 5, textureTimer);

	itemPowerUp = new PowerUp(
		{ 0, 0 }, { 150 , 0 }, 15, 15, 30,
		{ player1->GetX(), player1->GetY(), static_cast<float>(player1->GetWidth()), static_cast<float>(player1->GetHeight()) },
		textureShieldItem, textureShieldPicked);

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
		DrawMouse();
	}

	if (!player1->IsAlive())
	{
		DeathScreenDraw();
		DrawMouse();
	}

	DrawText("0.8", GetScreenWidth() - MeasureText("0.8", 40), GetScreenHeight() - MeasureText("0.8", 20), 20, WHITE);

	EndDrawing();
}

void UpdateGame()
{
	player1->Input(isGamePause);

	if (isGamePause)
	{
		setGameIsPaused(true);
	}
	else
	{
		setGameIsPaused(false);
	}

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
		//cout << "StairFloor" << endl;
		break;
	case ObjectsPatterns::StariCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(40)), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(50)), GetPercentageScreenHeight(20) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(60)), GetPercentageScreenHeight(30) });
		//cout << "StariCeiling" << endl;
		break;
	case ObjectsPatterns::WallFloor:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(65) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(55) - arrayObstacle[objectsToMove]->GetHeight() });
		//cout << "WallFloor" << endl;
		break;
	case ObjectsPatterns::WallCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(20) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetScreenWidth() / 2), GetPercentageScreenHeight(30) });
		//cout << "WallCeiling" << endl;
		break;
	case ObjectsPatterns::MountainFloor:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(75) - arrayObstacle[objectsToMove]->GetHeight() });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) - arrayObstacle[objectsToMove]->GetHeight() });
		//cout << "MountainFloor" << endl;
		break;
	case ObjectsPatterns::MountainCeiling:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2 + GetPercentageScreenWidth(30)), 0 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(10) });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), 0 });
		//cout << "MountainCeiling" << endl;
		break;
	case ObjectsPatterns::MidLine:
		arrayObstacle[objectsToMove]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(30), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 1]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(40), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 2]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(50), GetPercentageScreenHeight(85) / 2 });
		arrayObstacle[objectsToMove + 3]->SetPosition({ static_cast<float>(GetScreenWidth() * 2) + GetPercentageScreenWidth(60), GetPercentageScreenHeight(85) / 2 });
		//cout << "MidLine" << endl;
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
					itemPowerUp->SetDestroyed(true);
					itemPowerUp->ResetRandPosition();
					arrayObstacle[i]->SetDestroyed(true);
				}
				else
				{
					KillPlayer();
				}
				PlaySound(soundExplotion);
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
					if (!IsSoundPlaying(soundExplotion))
					{
						PlaySound(soundExplotion);
					}
					arrayObstacle[j]->setDeathAnimation();
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
		PlaySound(soundItemPicked);
	}

	if (!itemPowerUp->IsPicked())
	{
		if (player1->CheckColition(itemPowerUp->GetPosition(), itemPowerUp->GetWidth(), itemPowerUp->GetHeight()))
		{
			itemPowerUp->SetPicked(true);
			itemPowerUp->spawnItem->ResetTime();
			PlaySound(soundItemPicked);
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

		buttonDownVolumeMusic = new Buttons(
			{ GetPercentageScreenWidth(40) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(47),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
			RED, "-", 25);

		buttonUpVolumeMusic = new Buttons(
			{ GetPercentageScreenWidth(60) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(47),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
			RED, "+", 25);

		buttonDownVolumeSFX = new Buttons(
			{ GetPercentageScreenWidth(40) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(60),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
			RED, "-", 25);

		buttonUpVolumeSFX = new Buttons(
			{ GetPercentageScreenWidth(60) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(60),
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

	GameSoundManagment();

	paralax1->UpdateParalax(arrayObstacle[0]->getVelocityX());

	player1->SetPlayerGround();
	player1->Movement();
	player1->UpdateDraw();
	player1->AddDistanceMade(arrayObstacle[0]->getVelocityX() / 100 * GetFrameTime());

	//item logic
	if (itemTimer->holdTimer->GetIsTimeEnd())
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

	if (itemPowerUp->IsDestroyed())
	{
		itemPowerUp->spawnItem->UpdateTimer();

		if (itemPowerUp->spawnItem->GetIsTimeEnd())
		{
			itemPowerUp->SetDestroyed(false);
		}
	}
	else
	{
		itemPowerUp->UpdateItem();

		if (itemPowerUp->OutOfLimits())
		{
			itemPowerUp->ResetRandPosition();
		}
	}

	itemPowerUp->UpdatePositionPicked(player1->GetPosition());
	itemPowerUp->UpdateDraw();

	//obstacles logic
	ResetObstacleOutOfLimits();

	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i]->UpdateDraw();
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
	ClearBackground(Color{ 71,70,70, 255 });

	paralax1->DrawParalax();

	player1->Draw();

	//draw items
	itemTimer->Draw();
	itemPowerUp->Draw();

	//draw obstacles
	for (int i = 0; i < maxObstacles; i++)
	{
		arrayObstacle[i]->Draw();
		//if (arrayObstacle[i]->IsDestroyed())
		//{
		//	DrawRectangleLines(
		//		static_cast<int>(arrayObstacle[i]->GetX()),
		//		static_cast<int>(arrayObstacle[i]->GetY()),
		//		arrayObstacle[i]->GetWidth(),
		//		arrayObstacle[i]->GetHeight(),
		//		RED
		//	);
		//}
	}

	//draw bullets
	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsShootedNow())
		{
			player1->arrayBullets[i]->Draw();
		}
	}

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


	if (buttonUpVolumeMusic->IsButtonPressed())
	{
		setVolumeMusic(getVolumeMusic() + 0.1f);
	}

	if (buttonDownVolumeMusic->IsButtonPressed())
	{
		setVolumeMusic(getVolumeMusic() - 0.1f);
	}

	if (buttonUpVolumeSFX->IsButtonPressed())
	{
		setVolumeSFX(getVolumeSFX() + 0.1f);
	}

	if (buttonDownVolumeSFX->IsButtonPressed())
	{
		setVolumeSFX(getVolumeSFX() - 0.1f);
	}
}

void PauseDraw()
{
	paralax1->DrawParalax();

	DrawTexturePro(texturePauseBack,
		{ 0, 0, 128, 128 },
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(15)
		,GetPercentageScreenWidth(70),GetPercentageScreenHeight(70) },
		{ 0,	0, },
		0, WHITE);

	buttonResume->DrawButton();
	buttonBackToMenu->DrawButton();

	//music
	int volumeMusic = static_cast<int>(getVolumeMusic() * 10);

	DrawTextEx(gameFont, "Music", { GetPercentageScreenWidth(50) - MeasureText("Music", 25) / 2, GetPercentageScreenHeight(43) },
		25, GetPercentageScreenWidth(0.5), BLACK);

	DrawTexturePro(textureBlock,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(47),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(gameFont, TextFormat("%i", volumeMusic),
		{ GetPercentageScreenWidth(50) - MeasureText(TextFormat("%i", volumeMusic) , 25) / 2, GetPercentageScreenHeight(49) },
		25, GetPercentageScreenWidth(0.5), RED);

	buttonUpVolumeMusic->DrawButton();
	buttonDownVolumeMusic->DrawButton();

	//sfx
	int volumeSFX = static_cast<int>(getVolumeSFX() * 10);

	DrawTextEx(gameFont, "SFX", { GetPercentageScreenWidth(50) - MeasureText("SFX", 25) / 2, GetPercentageScreenHeight(55) },
		25, GetPercentageScreenWidth(0.5), BLACK);


	DrawTexturePro(textureBlock,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(7) / 2), GetPercentageScreenHeight(60),
			GetPercentageScreenWidth(7), GetPercentageScreenHeight(7) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(gameFont, TextFormat("%i", volumeSFX),
		{ GetPercentageScreenWidth(50) - MeasureText(TextFormat("%i", volumeSFX) , 25) / 2, GetPercentageScreenHeight(62) },
		25, GetPercentageScreenWidth(0.5), RED);

	buttonUpVolumeSFX->DrawButton();
	buttonDownVolumeSFX->DrawButton();
}

void DeathScreenUpdate()
{
	GameSoundManagment();

	if (!aliveButtons && !isButtonsCreated)
	{
		CreateGameButtons();
		isButtonsCreated = true;
	}

	if (static_cast<int>(player1->GetDistanceMade()) > highScore)
	{
		highScore = static_cast<int>(player1->GetDistanceMade());
		SaveStorageValue(0, highScore);
	}

	if (buttonBackToMenu->IsButtonPressed())
	{
		UnloadResourcesGame();
		setGameScene(GameScene::Menu);
	}

	if (buttonRestart->IsButtonPressed())
	{
		InitGameLoop();
	}
}

void DeathScreenDraw()
{
	paralax1->DrawParalax();

	DrawTexturePro(textureDeathScreen,
		{ 0, 0, 128, 128 },
		{ GetPercentageScreenWidth(15), GetPercentageScreenHeight(15)
		,GetPercentageScreenWidth(70),GetPercentageScreenHeight(70) },
		{ 0,	0, },
		0, WHITE);


	DrawTexturePro(textureBlock,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(17), GetPercentageScreenHeight(17)
		,GetPercentageScreenWidth(66),GetPercentageScreenHeight(50) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(
		gameFont, "Game Over",
		{ GetPercentageScreenWidth(50) - (MeasureText("Game Over", 40)) / 2, GetPercentageScreenHeight(20) },
		40, GetPercentageScreenWidth(1), RED);

	float high1 = 35;
	float high2 = 45;
	float high3 = 55;

	//total distance made
	DrawTextEx(
		gameFont, "Distance Runned :",
		{ GetPercentageScreenWidth(20), GetPercentageScreenHeight(high1) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())),
		{ GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 30) / 2),
		GetPercentageScreenHeight(high1) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, "m",
		{ GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())), 50) / 2),
		GetPercentageScreenHeight(high1) },
		30, GetPercentageScreenWidth(0.5), RED);

	//high score
	DrawTextEx(
		gameFont, "High score :",
		{ GetPercentageScreenWidth(20), GetPercentageScreenHeight(high2) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, TextFormat("%01i", highScore),
		{ GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", highScore), 30) / 2),
		GetPercentageScreenHeight(high2) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, "m",
		{ GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", highScore), 40) / 2),
		GetPercentageScreenHeight(high2) },
		30, GetPercentageScreenWidth(0.5), RED);

	//total distance save distance
	DrawTextEx(
		gameFont, "Total Distance :",
		{ GetPercentageScreenWidth(20),
		GetPercentageScreenHeight(high3) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, TextFormat("%01i", totalDistance),
		{ GetPercentageScreenWidth(65) - (MeasureText(TextFormat("%01i", totalDistance), 30) / 2),
		GetPercentageScreenHeight(high3) },
		30, GetPercentageScreenWidth(0.5), RED);

	DrawTextEx(
		gameFont, "m",
		{ GetPercentageScreenWidth(65) + (MeasureText(TextFormat("%01i", totalDistance), 40) / 2),
		GetPercentageScreenHeight(high3) },
		30, GetPercentageScreenWidth(0.5), RED);

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
	DrawTexturePro(textureClock,
		{ 0, 0, 63, 63 },
		{ GetPercentageScreenWidth(50) - (GetPercentageScreenWidth(11) / 2),
		0,GetPercentageScreenWidth(11),GetPercentageScreenHeight(11) },
		{ 0,	0, },
		0, WHITE);

	if (deathTimer->GetTimer() > 20)
	{
		DrawTextEx(
			gameFont, TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			{ GetPercentageScreenWidth(50) - (MeasureText("00", 50) / 2),
			GetPercentageScreenHeight(3), }, 50, GetPercentageScreenWidth(1), RED);
	}
	else if (deathTimer->GetTimer() > 10)
	{
		DrawTextEx(
			gameFont, TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			{ GetPercentageScreenWidth(50) - (MeasureText("10", 50) / 2),
			GetPercentageScreenHeight(3), }, 50, GetPercentageScreenWidth(1), RED);
	}
	else
	{

		DrawTextEx(
			gameFont, TextFormat("%01i", static_cast<int>(deathTimer->GetTimer())),
			{ GetPercentageScreenWidth(50) - (MeasureText("0", 50) / 2),
			GetPercentageScreenHeight(3), }, 50, GetPercentageScreenWidth(1), RED);
	}

	//meters
	DrawTexturePro(textureBlock,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(3), GetPercentageScreenHeight(90)
		,GetPercentageScreenWidth(40),GetPercentageScreenHeight(8) },
		{ 0,	0, },
		0, WHITE);

	DrawTextEx(
		gameFont, TextFormat("%01i", static_cast<int>(player1->GetDistanceMade())),
		{ GetPercentageScreenWidth(5),	GetPercentageScreenHeight(91), },
		50, GetPercentageScreenWidth(1), RED);

	DrawTextEx(
		gameFont, "m",
		{ GetPercentageScreenWidth(35),	GetPercentageScreenHeight(91) },
		50, GetPercentageScreenWidth(1), RED);

	//bullets

	DrawTexturePro(textureBlock,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(65), GetPercentageScreenHeight(90)
		,GetPercentageScreenWidth(30),GetPercentageScreenHeight(8) },
		{ 0,	0, },
		0, WHITE);

	DrawTexturePro(textureBullet,
		{ 0, 0, 64, 64 },
		{ GetPercentageScreenWidth(70), GetPercentageScreenHeight(90),
		64, 64 },
		{ 0,	0, },
		0, RED);

	DrawTextEx(
		gameFont, " = ",
		{ GetPercentageScreenWidth(70) + player1->arrayBullets[0]->GetWidth(), GetPercentageScreenHeight(91), },
		50, GetPercentageScreenWidth(1), RED);

	int bulletsPicked = 0;
	for (int i = 0; i < maxBullets; i++)
	{
		if (player1->arrayBullets[i]->IsPickedNow())
		{
			bulletsPicked += 1;
		}
	}

	if (bulletsPicked != 0)
	{
		DrawTextEx(
			gameFont, TextFormat("%01i", static_cast<int>(bulletsPicked)),
			{ GetPercentageScreenWidth(70) + player1->arrayBullets[0]->GetWidth() + (MeasureText(" = ", 50)),
			GetPercentageScreenHeight(91), },
			50, GetPercentageScreenWidth(1), RED);
	}
	else
	{
		DrawTextEx(
			gameFont, "X",
			{ GetPercentageScreenWidth(70) + player1->arrayBullets[0]->GetWidth() + (MeasureText(" = ", 50)),
			GetPercentageScreenHeight(91), },
			50, GetPercentageScreenWidth(1), RED);
	}
}

void KillPlayer()
{
	player1->SetIsAlive(false);
	totalDistance += static_cast<int>(player1->GetDistanceMade());
	SaveStorageValue(1, totalDistance);
}

void GameSoundManagment()
{
	SetSoundVolume(soundPlayerJump, getVolumeSFX());
	SetSoundVolume(soundPlayerFly, getVolumeSFX());
	SetSoundVolume(soundPlayerShoot, getVolumeSFX());
	SetSoundVolume(soundShieldActive, getVolumeSFX());

	if (player1->IsAlive())
	{

		if (IsKeyPressed(KEY_SPACE) && player1->IsPlayerGround())
		{
			PlaySound(soundPlayerJump);
		}

		if (IsKeyDown(KEY_SPACE) && !player1->IsPlayerGround())
		{
			if (!IsSoundPlaying(soundPlayerFly))
			{
				PlaySound(soundPlayerFly);
			}
		}
		else
		{
			PauseSound(soundPlayerFly);
		}

		int bulletsPicked = 0;
		for (int i = 0; i < maxBullets; i++)
		{
			if (player1->arrayBullets[i]->IsShootedNow())
			{
				bulletsPicked += 1;
			}
		}

		if (IsKeyPressed(KEY_F) && bulletsPicked != 5)
		{
			PlaySound(soundPlayerShoot);
		}

		if (itemPowerUp->IsPicked())
		{
			if (!IsSoundPlaying(soundShieldActive))
			{
				PlaySound(soundShieldActive);
			}
		}
		else
		{
			StopSound(soundShieldActive);
		}
	}
	else
	{
		StopSound(soundPlayerJump);
		StopSound(soundPlayerFly);
		StopSound(soundPlayerShoot);
		StopSound(soundShieldActive);
	}
}

void LoadResourcesGame()
{
	if (!isResoucesLoad)
	{
		texturePlayer = LoadTexture("res/textures/PlayerTexture.png");
		textureShieldItem = LoadTexture("res/textures/shield-item.png");
		textureShieldPicked = LoadTexture("res/textures/shield-picked.png");
		textureTimer = LoadTexture("res/textures/Timer-Item.png");
		textureObstacle = LoadTexture("res/textures/ObstacleTexture.png");
		textureBullet = LoadTexture("res/textures/bullet.png");
		textureExplotion = LoadTexture("res/textures/Explotion.png");
		textureClock = LoadTexture("res/textures/clock-timer.png");
		textureBlock = LoadTexture("res/textures/button.png");
		textureFloor = LoadTexture("res/textures/floor.png");
		textureWall1 = LoadTexture("res/textures/wall1.png");
		textureWall2 = LoadTexture("res/textures/wall2.png");
		textureWindow1 = LoadTexture("res/textures/window1.png");
		texturePauseBack = LoadTexture("res/textures/pauseBackground.png");
		textureDeathScreen = LoadTexture("res/textures/simpleBackground.png");

		soundPlayerJump = LoadSound("res/sounds/sfx/player-jump.wav");
		soundPlayerFly = LoadSound("res/sounds/sfx/player-fly.ogg");
		soundPlayerShoot = LoadSound("res/sounds/sfx/shoot-laser.ogg");
		soundShieldActive = LoadSound("res/sounds/sfx/shield.ogg");
		soundItemPicked = LoadSound("res/sounds/sfx/itemPicked.ogg");
		soundExplotion = LoadSound("res/sounds/sfx/explotion.ogg");

		gameFont = LoadFont("res/fonts/DS-DIGI.TTF");
	}

	isResoucesLoad = true;
}

void UnloadResourcesGame()
{
	UnloadTexture(texturePlayer);
	UnloadTexture(textureShieldItem);
	UnloadTexture(textureShieldPicked);
	UnloadTexture(textureTimer);
	UnloadTexture(textureObstacle);
	UnloadTexture(textureBullet);
	UnloadTexture(textureExplotion);
	UnloadTexture(textureClock);
	UnloadTexture(textureBlock);
	UnloadTexture(textureFloor);
	UnloadTexture(textureWall1);
	UnloadTexture(textureWall2);
	UnloadTexture(textureWindow1);
	UnloadTexture(texturePauseBack);
	UnloadTexture(textureDeathScreen);

	isResoucesLoad = false;
	isButtonsCreated = false;
}