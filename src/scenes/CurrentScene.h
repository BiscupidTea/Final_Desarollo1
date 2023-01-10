#include "raylib.h"

#include "scenes/Game.h"

enum class GameScene {
	Menu,
	GameLoop,
	Rules,
	Credits,
	Exit,
};

static GameScene gamescene;

void InitGame();

void ScreenScene(bool& IsRunning);