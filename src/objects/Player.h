#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	int points;
	int distanceMade;
	bool alive;

	Player(Vector2 position, Vector2 velocity, int width, int height, int distanceMade, int points, bool alive);
	~Player();

	void Draw();

	void Movement();

	void Input();

	bool IsAlive();

	int GetPoints();
	void AddPoint(int sumPoints);
};