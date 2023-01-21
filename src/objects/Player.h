#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Player : public Entity
{
private:
	int points;
	int distanceMade;
	bool alive;
	bool ground;
	bool jump;

public:
	Player(Vector2 position, Vector2 velocity, int width, int height, int distanceMade, int points, bool alive);
	~Player();

	void Draw();

	void Movement();

	void IsPlayerGround();

	void Input(bool& isPaused);

	bool IsAlive();

	int GetPoints();
	void AddPoint(int sumPoints);
};