#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Player : public Entity
{
public:
	int points;
	int distanceMade;
	bool alive;
	bool ground;
	bool jump;

	Player(Vector2 position, Vector2 velocity, int width, int height, int distanceMade, int points, bool alive);
	~Player();

	void Draw();

	void Movement();

	void IsPlayerGround();

	void Input();

	bool IsAlive();

	int GetPoints();
	void AddPoint(int sumPoints);
};