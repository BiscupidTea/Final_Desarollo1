#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	int points;
	bool alive;

	Player(Vector2 position, Vector2 velocity, int width, int height, int points, bool alive);
	~Player();

	void Draw();

	void Movement();

	void Input();

	bool IsAlive();

	int GetPoints();
	void AddPoint(int sumPoints);
};