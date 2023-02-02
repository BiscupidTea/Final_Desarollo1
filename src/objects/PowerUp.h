#pragma once
#include "Entity.h"

#include "tools/Timer.h"

class PowerUp :	public Entity
{
private:
	bool picked;
	Timer* spawnItem;

public:
	PowerUp(Vector2 position, Vector2 velocity, int width, int height);
	~PowerUp();

	void Draw();

	void Movement();

	bool OutOfLimits();

	void SetPicked(bool setter);
	bool IsPicked();
};

