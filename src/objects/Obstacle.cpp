#include "Obstacle.h"

Obstacle::Obstacle(Vector2 position, Vector2 velocity, int width, int height, Texture2D textureObstacle) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;

	this->textureObstacle = textureObstacle;
	this->width = textureObstacle.width / 5;
	this->height = textureObstacle.height;

	this->destroyed = false;

	changeFrame = new Timer(0.2f);

}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw()
{
	//logic texture
	changeFrame->UpdateTimer();

	if (changeFrame->GetIsTimeEnd())
	{
		actualFrame += 1;

		if (actualFrame > 4)
		{
			actualFrame = 0;
		}

		changeFrame->ResetTime();
	}

	float sumSource = static_cast<float>(0 + (64 * actualFrame));

	//draw hitbox and texture
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), RED);
	DrawTexturePro(textureObstacle,
		{ sumSource, 0, 64, 64 },
		{ position.x,position.y, 64, 64 },
		{ 0,	0, },
		0, WHITE);
}

void Obstacle::Movement()
{
	position.x -= velocity.x * GetFrameTime();
}

bool Obstacle::OutOfLimits()
{
	if (GetX() + width < 0)
	{
		return true;
	}

	return false;
}

void Obstacle::SetDestroyed(bool setter)
{
	destroyed = setter;
}

bool Obstacle::IsDestroyed()
{
	return destroyed;
}