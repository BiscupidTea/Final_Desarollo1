#pragma once
#include "tools/tools.h"
#include "tools/Timer.h"

#include "Entity.h"

class Obstacle : public Entity
{
private:
	bool destroyed;

	Timer* changeFrame;
	Texture2D textureObstacle;
	int actualFrame;

public:
	Obstacle(
		Vector2 position, Vector2 velocity,
		int width, int height,
		Texture2D textureObstacle);
	~Obstacle();

	void Draw();

	void Movement();

	bool OutOfLimits();

	void SetDestroyed(bool setter);
	bool IsDestroyed();
};