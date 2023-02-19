#pragma once
#include "tools/Timer.h"

#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
private:
	int points;
	float distanceMade;
	bool alive;
	bool ground;
	bool jump;
	static const int maxBullets = 5;

	Timer* changeFrame;
	Texture2D texturePlayer;
	int actualFrame;

public:
	Bullet* arrayBullets[maxBullets];

	Player(
		Vector2 position, Vector2 velocity, 
		float distanceMade, int points, bool alive, 
		Texture2D texturePlayer, Texture2D textureBullet);

	~Player();

	void Draw();

	void UpdateDraw();

	void Movement();

	void SetPlayerGround();
	bool IsPlayerGround();

	void Input(bool& isPaused);

	bool IsAlive();
	void SetIsAlive(bool aliveState);

	int GetPoints();
	void AddPoint(int sumPoints);

	float GetDistanceMade();
	void AddDistanceMade(float sumDistance);
};