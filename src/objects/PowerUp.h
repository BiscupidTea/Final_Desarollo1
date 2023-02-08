#pragma once
#include "Entity.h"

#include "tools/Tools.h"
#include "tools/Timer.h"

class PowerUp :	public Entity
{
private:
	bool picked;
	bool destroyed;
	Texture2D shieldTextureItem;
	Texture2D shieldTexturePicked;
	Rectangle playerSpec;
	Timer* changeFrame;
	int actualFrame;

public:
	Timer* spawnItem;
	PowerUp(Vector2 position, Vector2 velocity, 
		int width, int height, 
		float spawnTime, 
		Rectangle playerSpec,
		Texture2D shieldTextureItem,
		Texture2D shieldTexturePicked
		);
	~PowerUp();

	void Draw();

	void UpdateItem();
	void UpdatePositionPicked(Vector2 playerUpdateXY);
	void UpdateDraw();

	bool OutOfLimits();
	void ResetRandPosition();

	void SetPicked(bool setter);
	bool IsPicked();

	void SetDestroyed(bool setter);
	bool IsDestroyed();
};

