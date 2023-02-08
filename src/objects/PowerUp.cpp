#include "PowerUp.h"

PowerUp::PowerUp(Vector2 position, Vector2 velocity, int width, int height, float spawnTime, Rectangle playerSpec, Texture2D shieldTextureItem, Texture2D shieldTexturePicked) : Entity(position, velocity, width, height)
{
	this->shieldTextureItem = shieldTextureItem;
	this->shieldTexturePicked = shieldTexturePicked;
	this->width = shieldTextureItem.width;
	this->height = shieldTextureItem.height;

	this->position = position;
	this->velocity = velocity;

	this->picked = false;

	this->spawnItem = new Timer(spawnTime);

	this->playerSpec = playerSpec;

	changeFrame = new Timer(0.2f);
}

PowerUp::~PowerUp()
{

}

void PowerUp::Draw()
{
	//DrawRectangle(static_cast<int>(GetX()), static_cast<int>(GetY()), width, height, SKYBLUE);
	if (IsPicked())
	{
		float sumSource = static_cast<float>(0 + (64 * actualFrame));
		DrawTexturePro(shieldTexturePicked,
			{ sumSource,0,64,64 },
			{ playerSpec.x - playerSpec.width / 4,
			playerSpec.y - playerSpec.height / 8,
			75, 75 },
			{ 0,0 }, 0, WHITE
		);
	}
	else
	{
		DrawTexturePro(shieldTextureItem,
			{ 0, 0, 64, 64 },
			{ position.x,position.y, 64, 64 },
			{ 0,	0, },
			0, WHITE);
	}
}

void PowerUp::UpdateItem()
{
	position.x -= velocity.x * GetFrameTime();
}

void PowerUp::UpdatePositionPicked(Vector2 playerUpdateXY)
{
	playerSpec.x = playerUpdateXY.x;
	playerSpec.y = playerUpdateXY.y;
}

void PowerUp::UpdateDraw()
{
	changeFrame->UpdateTimer();

	if (changeFrame->GetIsTimeEnd())
	{
		actualFrame += 1;

		if (actualFrame > 7)
		{
			actualFrame = 0;
		}

		changeFrame->ResetTime();
	}
}

bool PowerUp::OutOfLimits()
{
	if (GetX() + width < 0)
	{
		return true;
	}

	return false;
}

void PowerUp::SetPicked(bool setter)
{
	picked = setter;
}

bool PowerUp::IsPicked()
{
	return picked;
}

void PowerUp::ResetRandPosition()
{
	float midPlayableScreen = GetPercentageScreenHeight(42.5);
	position.x = static_cast<float>(GetScreenWidth());

	if (GetRandomValue(1, 2) == 1)
	{
		position.y = midPlayableScreen - (midPlayableScreen / 2);
	}
	else
	{
		position.y = midPlayableScreen + (midPlayableScreen / 2);
	}

	spawnItem->ResetTime();
}