#include "SceneSetter.h"

extern GameScene gameScene;

void setGameScene(GameScene newGameScene)
{
	gameScene = newGameScene;

	cout << "change scene to : ";
	switch (gameScene)
	{
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