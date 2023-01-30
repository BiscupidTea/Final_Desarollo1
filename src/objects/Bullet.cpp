#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 velocity, int width, int height, bool isShooted) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->isShooted = isShooted;
}

Bullet::~Bullet()
{

}

void Bullet::Draw()
{
	DrawRectangle(position.x, position.y, width, height, BROWN);
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
}

void Bullet::ResetPosition()
{
	position.x = GetPercentageScreenWidth(-50);
	position.y = GetPercentageScreenHeight(-50);
}

bool Bullet::OutOfLimits()
{
	if (position.x > GetScreenWidth())
	{
		ResetPosition();
	}
}