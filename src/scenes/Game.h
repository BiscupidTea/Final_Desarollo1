#include <iostream>
#include "raylib.h"

#include "tools/tools.h"
#include "tools/Buttons.h"
#include "tools/Timer.h"

#include "scenes/SceneSetter.h"

#include "objects/Player.h"
#include "objects/Obstacle.h"

using namespace std;

void InitGameLoop();

void GameLoopScene();

void DrawGame();

void UpdateGame();

void InitPlayer();

void ResetObstacle();

void ResetObstacleOutOfLimits();

void SetObstaclePattern();

void CheckColitions();

void CreateGameButtons();

void GameplayUpdate();

void GameplayDraw();

void PauseUpdate();

void PauseDraw();

void DeathScreenUpdate();

void DeathScreenDraw();