#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Bullet : public Entity
{
private:
	bool isShooted;
	bool isPicked;

	Texture2D textureBullet;

public:
	Bullet(
		Vector2 position, Vector2 velocity, 
		int width, int height, bool isPicked,
		Texture2D textureBullet);
	~Bullet();

	void Draw();

	void UpdateBullet();

	void ShootBullet(Vector2 positionsBullet);

	void ResetPosition();

	void OutOfLimits();

	bool IsShootedNow();

	bool IsPickedNow();

	void SetIsPicked(bool setter);

	void SetIsShooted(bool setter);
};

