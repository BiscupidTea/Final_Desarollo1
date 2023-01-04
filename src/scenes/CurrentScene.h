#include "raylib.h"

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