#include "Player.h"

Player::Player(Vector2 position, Vector2 velocity, int width, int height, int distanceMade, int points, bool alive) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->distanceMade = distanceMade;
	this->points = points;
	this->alive = alive;
	ground = false;
	jump = false;
}

Player::~Player()
{

}

void Player::Draw()
{
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), BLUE);
}

void Player::Movement()
{
	if (!ground && !jump)
	{
		velocity.y += 500 * GetFrameTime();
	}
	else if (!ground && jump)
	{
		if (velocity.y > -300)
		{
			velocity.y -= 450 * GetFrameTime();
		}
	}
	else if (ground && jump)
	{
		ground = false;
		velocity.y = -200;
	}
	else if (ground)
	{
		velocity.y = 0;
	}

	if (position.y < 0)
	{
		velocity.y = 0;
		position.y = 0;
	}

	position.y += velocity.y * GetFrameTime();
}

void Player::IsPlayerGround()
{
	float florDistance = GetPercentageScreenHeight(85.0f);

	if (position.y + height < florDistance)
	{
		ground = false;
	}
	else
	{
		ground = true;
	}
}

void Player::Input(bool& isPaused)
{
	if (isPaused)
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			isPaused = false;
		}
	}
	else
	{
		if (IsKeyDown(KEY_SPACE))
		{
			jump = true;
		}
		else
		{
			jump = false;
		}

		if (IsKeyPressed(KEY_ESCAPE))
		{
			isPaused = true;
		}
	}
}

bool Player::IsAlive()
{
	return alive;
}

void Player::SetIsAlive(bool aliveState)
{
	alive = aliveState;
}

int Player::GetPoints()
{
	return points;
}

void Player::AddPoint(int sumPoints)
{
	points += sumPoints;
}