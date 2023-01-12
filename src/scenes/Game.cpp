#include "Game.h"

Player* player1 = new Player({ 0, 0 },{ 0, 50 }, 40, 60, 0, 0, true);

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
}

void InitPlayer()
{
	player1->SetPosition({ GetPercentageScreenWidth(10.0f),GetPercentageScreenHeight(85.0f) - player1->GetHeight() });
}
