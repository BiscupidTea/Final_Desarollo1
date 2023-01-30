#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Bullet : public Entity
{
private:
	bool isShooted;

public:
	Bullet(
		Vector2 position, Vector2 velocity, 
		int width, int height, bool isShooted);
	~Bullet();

	void Draw();

	void UpdateBullet();

	void ShootBullet(Vector2 positionsBullet);

	void ResetPosition();

	bool OutOfLimits();
};

