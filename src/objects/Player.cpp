#include "Player.h"

Player::Player(Vector2 position, Vector2 velocity, float distanceMade, int points, bool alive, Texture2D texturePlayer, Texture2D textureBullet) : Entity(position, velocity, width, height)
{
	this->position = position;
	this->velocity = velocity;

	this->texturePlayer = texturePlayer;

	this->width = texturePlayer.width / 9;
	this->height = texturePlayer.height;

	this->distanceMade = distanceMade;
	this->points = points;
	this->alive = alive;
	ground = false;
	jump = false;

	this->actualFrame = 0;

	changeFrame = new Timer(0.3f);

	for (int i = 0; i < maxBullets; i++)
	{
		arrayBullets[i] = new Bullet({ -500, -500 }, { 400, 0 }, 20, 20, true, textureBullet);
	}
}

Player::~Player()
{

}

void Player::Draw()
{
	//logic texture
	changeFrame->UpdateTimer();
	cout << changeFrame->GetTimer() << endl;

	if (ground)
	{
		if (actualFrame < 5)
		{
			actualFrame = 5;
		}

		if (changeFrame->GetIsTimeEnd())
		{
			actualFrame += 1;

			if (actualFrame >= 9)
			{
				actualFrame = 5;
			}

			changeFrame->ResetTime();
		}
	}

	if (jump)
	{
		if (actualFrame < 1 && actualFrame > 4)
		{
			actualFrame = 1;
		}

		if (changeFrame->GetIsTimeEnd())
		{
			actualFrame += 1;

			if (actualFrame >= 5)
			{
				actualFrame = 1;
			}

			changeFrame->ResetTime();
		}
	}
	
	if (!jump && !ground)
	{
		actualFrame = 0;
	}

	float sumSource = static_cast<float>(0 + (64 * actualFrame));

	//draw hitbox and texture
	DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), GetWidth(), GetHeight(), BLUE);
	DrawTexturePro(texturePlayer,
		{ sumSource, 0, 64, 64 },
		{ position.x,position.y, 64, 64 },
		{ 0,	0, },
		0, WHITE);
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

		if (IsKeyPressed(KEY_F))
		{
			for (int i = 0; i < maxBullets; i++)
			{
				if (arrayBullets[i]->IsPickedNow())
				{
					arrayBullets[i]->ShootBullet(GetPosition());
					cout << "fire" << endl;
					break;
				}
			}
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

float Player::GetDistanceMade()
{
	return distanceMade;
}

void Player::AddDistanceMade(float sumDistance)
{
	distanceMade += sumDistance;
}