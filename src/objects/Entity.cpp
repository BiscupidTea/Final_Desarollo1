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

void Entity::SetPosition(Vector2 position)
{
	this->position = position;
}

Vector2 Entity::GetPosition()
{
	return position;
}

void Entity::setVelocityX(int velX)
{
	velocity.x = velX;
}

void Entity::setVelocityY(int velY)
{
	velocity.y = velY;
}

int Entity::getVelocityX()
{
	return velocity.x;
}

int Entity::getVelocityY()
{
	return velocity.y;
}

int Entity::GetX()
{
	return position.x;
}

int Entity::GetY()
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
