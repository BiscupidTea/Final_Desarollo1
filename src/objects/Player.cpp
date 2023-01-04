#include "Player.h"

Player::Player(Vector2 position, Vector2 velocity, int width, int height, int points, bool alive) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
	this->points = points;
	this->alive = alive;
}

Player::~Player()
{

}

void Player::Draw()
{
	DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight(), RED);
}

void Player::Movement()
{
	position.y += velocity.y * GetFrameTime();
}

void Player::Input()
{
	if (IsKeyDown(KEY_SPACE))
	{
		velocity.y = -10;
	}
}

bool Player::IsAlive()
{
	return alive;
}

int Player::GetPoints()
{
	return points;
}

void Player::AddPoint(int sumPoints)
{
	points += sumPoints;
}