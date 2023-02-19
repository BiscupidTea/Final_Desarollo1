#include "Paralax.h"

#include <iostream>
#include "tools/tools.h"

Paralax::Paralax(float velocityFloors, 
	Texture2D textureFloor, Texture2D textureWall1, Texture2D textureWall2, Texture2D textureWindow1)
{
	this->positionFloorY = GetPercentageScreenHeight(85);
	this->ScrollingFloor = 0;
	this->velocityFloors = velocityFloors;

	this->positionWallY = 0;
	this->ScrollingWall1 = 0;
	this->ScrollingWall2 = (textureWall1.width * 6.25f) + ScrollingWall1;
	this->velocityWalls = velocityFloors / 4;

	
	this->positionWindow = { GetPercentageScreenWidth(12) , GetPercentageScreenHeight(17) };
	this->tipeWindow = GetRandomValue(1, 6);
	this->velocityWindow = velocityWalls / 2;

	this->textureFloor = textureFloor;
	this->textureWall1 = textureWall1;
	this->textureWall2 = textureWall2;
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
	DrawTexturePro(textureFloor,
		{ 0,0, 128, 19 },
		{ ScrollingFloor ,  positionFloorY,
		static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(15) },
		{ 0,0 },
		0, WHITE
	);

	DrawTexturePro(textureFloor,
		{ 0,0, 128, 19 },
		{ (textureFloor.width * 6.25f)  + ScrollingFloor ,positionFloorY ,
		static_cast<float>(GetScreenWidth()), GetPercentageScreenHeight(15) },
		{ 0,0 },
		0, WHITE
	);

}

void Paralax::DrawWall()
{
	DrawTexturePro(textureWall1,
		{ 0,0, 128, 109 },
		{ ScrollingWall1 ,  positionWallY,
		textureFloor.width * 6.25f, GetPercentageScreenHeight(85) },
		{ 0,0 },
		0, WHITE
	);

	DrawTexturePro(textureWall2,
		{ 0,0, 128, 109 },
		{ ScrollingWall2 ,positionWallY ,
		textureFloor.width * 6.25f, GetPercentageScreenHeight(85) },
		{ 0,0 },
		0, WHITE
	);
}

void Paralax::DrawWindow()
{
	DrawTexturePro(textureWindow1,
		{ 0,0, 100, 64 },
		{ positionWindow.x ,positionWindow.y ,
		textureWindow1.width * 6.25f, textureWindow1.height * 6.25f },
		{ 0,0 },
		0, WHITE
	);
}

void Paralax::UpdateParalax(float velocityObstacles)
{
	velocityFloors = velocityObstacles;
	velocityWalls = velocityFloors / 4;
	velocityWindow = velocityWalls / 2;

	UpdateWindow();
	UpdateWall();
	UpdateFloor();
}

void Paralax::UpdateFloor()
{
	ScrollingFloor -= velocityFloors * GetFrameTime();
	if (ScrollingFloor <= -(textureFloor.width * 6.25f))
	{
		ScrollingFloor = 0;
	}
}

void Paralax::UpdateWall()
{
	ScrollingWall1 -= velocityWalls * GetFrameTime();
	if (ScrollingWall1 <= -(textureWall1.width * 6.25f))
	{
		ScrollingWall1 = ScrollingWall2 + (textureWall2.width * 6.25f);
		positionWindow.x = ScrollingWall2 + (textureWall2.width * 6.25f) + GetPercentageScreenWidth(12);
	}

	ScrollingWall2 -= velocityWalls * GetFrameTime();
	if (ScrollingWall2 <= -(textureWall2.width * 6.25f))
	{
		ScrollingWall2 = ScrollingWall1 + (textureWall1.width * 6.25f);
	}
}

void Paralax::UpdateWindow()
{
	positionWindow.x -= velocityWalls * GetFrameTime();
}