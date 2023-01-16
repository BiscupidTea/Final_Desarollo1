#include "Game.h"

static const int maxObstacles = 5;

Player* player1;
Obstacle* arrayobstacle[maxObstacles];

void InitGameLoop()
{
	player1 = new Player({ 0, 0 }, { 0, 50 }, 40, 60, 0, 0, true);
	for (int i = 0; i < maxObstacles; i++)
	{
		arrayobstacle[i] = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60);
	}

	InitPlayer();
}

void GameLoopScene()
{
	DrawGame();

	UpdateGame();
}

void DrawGame()
{
	BeginDrawing();
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

	EndDrawing();
}

void UpdateGame()
{
	player1->Input();
	player1->IsPlayerGround();
	player1->Movement();

	InitObstacle();
	for (int i = 0; i < maxObstacles; i++)
	{
		arrayobstacle[i]->Movement();
	}

	CheckColitions();
}

void InitPlayer()
{
	player1->SetPosition({ GetPercentageScreenWidth(10.0f),GetPercentageScreenHeight(85.0f) - player1->GetHeight() });
}

void InitObstacle()
{
	for (int i = 0; i < maxObstacles; i++)
	{
		if (arrayobstacle[i]->OutOfLimits())
		{
			arrayobstacle[i]->SetPosition({
				GetPercentageScreenWidth(100.0f),
				static_cast<float>(GetRandomValue(0, (static_cast<int>(GetPercentageScreenHeight(85.0f)) - (arrayobstacle[i]->GetHeight()))))
				});
			cout << arrayobstacle[i]->GetY() << endl;
		}
	}
}

void CheckColitions()
{
	for (int i = 0; i < maxObstacles; i++)
	{
		if (player1->CheckColition(arrayobstacle[i]->GetPosition(), arrayobstacle[i]->GetWidth(), arrayobstacle[i]->GetHeight()))
		{
			setGameScene(GameScene::Menu);
			arrayobstacle[i]->SetPosition({
		GetPercentageScreenWidth(100.0f),
		static_cast<float>(GetRandomValue(0, (static_cast<int>(GetPercentageScreenHeight(85.0f)) - (arrayobstacle[i]->GetHeight())))) });

			cout << arrayobstacle[i]->GetY() << endl;
		}
	}
}