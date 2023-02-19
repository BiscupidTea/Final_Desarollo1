#include "Bullet.h"

#include "tools/tools.h"

Bullet::Bullet(Vector2 position, Vector2 velocity, int width, int height, bool isPicked, Texture2D textureBullet) : Entity(position, velocity, width, height)
{
	this->textureBullet = textureBullet;
	this->width = textureBullet.width;
	this->height = textureBullet.height / 2;

	this->position = position;
	this->velocity = velocity;
	this->isPicked = isPicked;
	this->isShooted = false;
}

Bullet::~Bullet()
{

}

void Bullet::Draw()
{
	//DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), width, height, BROWN);
	DrawTexturePro(textureBullet,
		{ 0, 0, 64, 64 },
		{ position.x,position.y-height/2, 64, 64 },
		{ 0,	0, },
		0, WHITE);
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