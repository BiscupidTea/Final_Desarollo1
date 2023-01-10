#include "Entity.h"

Entity::Entity(Vector2 position, Vector2 velocity, int width, int height)
{
	this->position = position;
	this->velocity = velocity;
	this->width = width;
	this->height = height;
}

Entity::~Entity()
{

}

void Entity::SetPosition(Vector2 newPosition)
{
	this->position = newPosition;
}

Vector2 Entity::GetPosition()
{
	return position;
}

void Entity::setVelocityX(float velX)
{
	velocity.x = velX;
}

void Entity::setVelocityY(float velY)
{
	velocity.y = velY;
}

float Entity::getVelocityX()
{
	return velocity.x;
}

float Entity::getVelocityY()
{
	return velocity.y;
}

float Entity::GetX()
{
	return position.x;
}

float Entity::GetY()
{
	return position.y;
}

int Entity::GetWidth()
{
	return this->width;
}

int Entity::GetHeight()
{
	return this->height;
}
