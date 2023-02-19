#include "SceneSetter.h"

extern GameScene gameScene;

bool gameIsPaused;

float volumeMusic;
float volumeSFX;

void setGameScene(GameScene newGameScene)
{
	gameScene = newGameScene;

	cout << "change scene to : ";
	switch (gameScene)
	{
	case GameScene::SplashScreen:
		cout << "SplashScreen" << endl;
		break;
	case GameScene::Menu:
		cout << "Menu" << endl;
		break;
	case GameScene::GameLoop:
		cout << "GameLoop" << endl;
		break;
	case GameScene::Rules:
		cout << "Rules" << endl;
		break;
	case GameScene::Options:
		cout << "Options" << endl;
		break;
	case GameScene::Credits:
		cout << "Credits" << endl;
		break;
	case GameScene::Exit:
		cout << "Exit" << endl;
		break;
	default:
		break;
	}
}

bool getGameIsPaused()
{
	return gameIsPaused;
}

void setGameIsPaused(bool modifier)
{
	gameIsPaused = modifier;
}

float getVolumeMusic()
{
	return volumeMusic;
}

void setVolumeMusic(float newValue)
{
	volumeMusic = newValue;
	if (volumeMusic > 1)
	{
		volumeMusic = 1.0f;
	}

	if (volumeMusic < 0.1f)
	{
		volumeMusic = 0;
	}

	cout << volumeMusic << endl;
}

float getVolumeSFX()
{
	return volumeSFX;
}

void setVolumeSFX(float newValue)
{
	volumeSFX = newValue;
	if (volumeSFX > 1)
	{
		volumeSFX = 1.0f;
	}

	if (volumeSFX < 0.1f)
	{
		volumeSFX = 0;
	}
}