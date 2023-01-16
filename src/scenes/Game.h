#include <iostream>
#include "raylib.h"
#include "tools/tools.h"

#include "scenes/SceneSetter.h"

#include "objects/Player.h"
#include "objects/Obstacle.h"

using namespace std;

void GameLoopScene();

void DrawGame();

void UpdateGame();

void InitPlayer();

void InitObstacle();

void CheckColitions();