#pragma once
#include "Entity.h"

#include "tools/Tools.h"
#include "tools/Timer.h"

class PowerUp :	public Entity
{
private:
	bool picked;
	Texture2D shieldTexture;

public:
	Timer* spawnItem;
	PowerUp(Vector2 position, Vector2 velocity, 
		int width, int height, 
		float spawnTime, 
		Texture2D shieldTexture);
	~PowerUp();

	void Draw();

	void UpdateItem();

	bool OutOfLimits();
	void ResetRandPosition();

	void SetPicked(bool setter);
	bool IsPicked();
};

