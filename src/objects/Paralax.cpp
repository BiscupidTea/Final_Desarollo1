#include "Paralax.h"

Paralax::Paralax(float velocityFloors, Texture2D textureFloor, Texture2D textureWall1, Texture2D textureWindow1)
{
	this->positionFloor1 = { 0, GetPercentageScreenHeight(85) };
	this->positionFloor2 = { static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(85) };

	this->positionWall1 = { 0, 0 };
	this->positionWall2 = { static_cast<float>(GetScreenWidth()), 0 };

	this->positionWindow = { GetPercentageScreenWidth(15) , GetPercentageScreenHeight(15) };
	this->tipeWindow = GetRandomValue(1, 6);

	this->velocityFloors = velocityFloors;
	this->velocityWalls = velocityFloors / 4;
	this->velocityWindow = velocityWalls / 2;

	this->textureFloor = textureFloor;
	this->textureWall1 = textureWall1;
	this->textureWindow1 = textureWindow1;
}

Paralax::~Paralax()
{

}

void Paralax::DrawParalax()
{
	DrawWindow();
	DrawWall();
	DrawFloor();
}

void Paralax::DrawFloor()
{
	//DrawTexture(textureFloor,
	//	static_cast<int>(positionFloor1.x),
	//	static_cast<int>(positionFloor1.y), WHITE);

	//DrawTexture(textureFloor,
	//	static_cast<int>(positionFloor2.x),
	//	static_cast<int>(positionFloor2.y), WHITE);

	DrawTexturePro(textureFloor,
		{ 0,0, 128, 19 },
		{ positionFloor1.x ,positionFloor1.y ,
		static_cast<float>(800), static_cast<float>(120) },
		{ 0,0 },
		0, WHITE
	);

}

void Paralax::DrawWall()
{
	DrawTexturePro(textureWall1,
		{ 0,0, 128, 109 },
		{ positionWall1.x ,positionWall1.y ,
		static_cast<float>(800), static_cast<float>(680) },
		{ 0,0 },
		0, WHITE
	);

	//DrawTexture(textureWall1,
	//	static_cast<int>(positionWall2.x),
	//	static_cast<int>(positionWall2.y), WHITE);
}

void Paralax::DrawWindow()
{
	//DrawTexture(textureWindow1,
	//	static_cast<int>(positionWindow.x),
	//	static_cast<int>(positionWindow.y), WHITE);
}

void Paralax::UpdateParalax()
{
	UpdateFloor();
	UpdateWall();
	UpdateWindow();
}

void Paralax::UpdateFloor()
{
	positionFloor1.x -= velocityFloors * GetFrameTime();
	if (positionFloor1.x + 150 < 0)
	{
		positionFloor1.x = GetPercentageScreenWidth(100);
	}

	positionFloor2.x -= velocityFloors * GetFrameTime();
	if (positionFloor2.x + 150 < 0)
	{
		positionFloor2.x = GetPercentageScreenWidth(100);
	}
}

void Paralax::UpdateWall()
{
	positionWall1.x -= velocityWalls * GetFrameTime();
	if (positionWall1.x + textureWall1.width < 0)
	{
		positionWall1.x = GetPercentageScreenWidth(100);
	}

	positionWall2.x -= velocityWalls * GetFrameTime();
	if (positionWall2.x + textureWall1.width < 0)
	{
		positionWall2.x = GetPercentageScreenWidth(100);
	}
}

void Paralax::UpdateWindow()
{
	positionWindow.x -= velocityWindow * GetFrameTime();
	if (positionWindow.x + textureWindow1.width < 0)
	{
		positionWindow.x = GetPercentageScreenWidth(100);
	}
}