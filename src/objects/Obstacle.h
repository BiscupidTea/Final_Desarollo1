#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Obstacle : public Entity
{
private:


public:
	Obstacle(Vector2 position, Vector2 velocity, int width, int height);
	~Obstacle();

	void Draw();

	void Movement();

	bool OutOfLimits();
};