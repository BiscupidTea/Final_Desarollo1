#pragma once
#include <iostream>

using namespace std;

enum class GameScene {
	Menu,
	GameLoop,
	Rules,
	Options,
	Credits,
	Exit,
};

void setGameScene(GameScene newGameScene);

bool getGameIsPaused();

void setGameIsPaused(bool modifier);

float getVolumeMusic();

void setVolumeMusic(float newValue);

float getVolumeSFX();

void setVolumeSFX(float newValue);