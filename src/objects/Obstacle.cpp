#include "Obstacle.h"

Obstacle::Obstacle(Vector2 position, Vector2 velocity, int width, int height, Texture2D textureObstacle) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;

	this->textureObstacle = textureObstacle;
	this->width = textureObstacle.width / 6;
	this->height = textureObstacle.height;

	this->destroyed = false;
	this->actualFrame = 0;

	changeFrame = new Timer(0.2f);

}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw()
{
	float sumSource = static_cast<float>(0 + (64 * actualFrame));
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), WHITE);
	DrawTexturePro(textureObstacle,
		{ sumSource, 0, 64, 64 },
		{ position.x - (textureObstacle.width / 70),position.y, 64, 64 },
		{ 0,	0, },
		0, WHITE);
}

void Obstacle::UpdateDraw()
{
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