#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 velocity, int width, int height, bool isPicked) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->isPicked = isPicked;
	this->isShooted = false;
}

Bullet::~Bullet()
{

}

void Bullet::Draw()
{
	DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), width, height, BROWN);
}

void Bullet::UpdateBullet()
{
	if (isShooted)
	{
		position.x += velocity.x * GetFrameTime();
	}
}

void Bullet::ShootBullet(Vector2 positionsBullet)
{
	position = positionsBullet;
	isShooted = true;
	isPicked = false;
}

void Bullet::ResetPosition()
{
	position.x = GetPercentageScreenWidth(-50);
	position.y = GetPercentageScreenHeight(-50);
}

void Bullet::OutOfLimits()
{
	if (position.x > GetScreenWidth())
	{
		ResetPosition();
	}
}

bool Bullet::IsShootedNow()
{
	return isShooted;
}

bool Bullet::IsPickedNow()
{
	return isPicked;
}

void Bullet::SetIsPicked(bool setter)
{
	isPicked = setter;
}

void Bullet::SetIsShooted(bool setter)
{
	isShooted = setter;
}