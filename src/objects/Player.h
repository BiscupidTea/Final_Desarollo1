#pragma once
#include <iostream>
#include "tools/tools.h"

#include "Entity.h"

#include "Bullet.h"
using namespace std;

class Player : public Entity
{
private:
	int points;
	float distanceMade;
	bool alive;
	bool ground;
	bool jump;
	static const int maxBullets = 5;

public:
	Bullet* arrayBullets[maxBullets];

	Player(
		Vector2 position, Vector2 velocity,
		int width, int height, 
		float distanceMade, int points,
		bool alive);

	~Player();

	void Draw();

	void Movement();

	void IsPlayerGround();

	void Input(bool& isPaused);

	bool IsAlive();
	void SetIsAlive(bool aliveState);

	int GetPoints();
	void AddPoint(int sumPoints);

	float GetDistanceMade();
	void AddDistanceMade(float sumDistance);
};