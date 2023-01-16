#include "Game.h"

Player* player1 = new Player({ 0, 0 }, { 0, 50 }, 40, 60, 0, 0, true);
Obstacle* obstacle1 = new Obstacle({ -10, 0 }, { 300, 0 }, 40, 60);

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
	obstacle1->Draw();

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
	obstacle1->Movement();

	CheckColitions();
}

void InitPlayer()
{
	player1->SetPosition({ GetPercentageScreenWidth(10.0f),GetPercentageScreenHeight(85.0f) - player1->GetHeight() });
}

void InitObstacle()
{
	if (obstacle1->OutOfLimits())
	{
		obstacle1->SetPosition({
			GetPercentageScreenWidth(100.0f),
			static_cast<float>(GetRandomValue(0, (static_cast<int>(GetPercentageScreenHeight(85.0f)) - (obstacle1->GetHeight()))))
		});
		cout << obstacle1->GetY() << endl;
	}
}

void CheckColitions()
{
	if (player1->CheckColition(obstacle1->GetPosition(), obstacle1->GetWidth(), obstacle1->GetHeight()))
	{
		setGameScene(GameScene::Menu);
		obstacle1->SetPosition({
	GetPercentageScreenWidth(100.0f),
	static_cast<float>(GetRandomValue(0, (static_cast<int>(GetPercentageScreenHeight(85.0f)) - (obstacle1->GetHeight())))) });
		cout << obstacle1->GetY() << endl;
	}
}