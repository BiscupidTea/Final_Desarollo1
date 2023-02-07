#pragma once
#include "raylib.h"
#include "tools/tools.h"

class Paralax
{
private:
	Vector2 positionFloor1;
	Vector2 positionFloor2;
	float velocityFloors;

	Vector2 positionWall1;
	Vector2 positionWall2;
	float velocityWalls;

	int tipeWindow;
	Vector2 positionWindow;
	float velocityWindow;


	Texture2D textureFloor;

	Texture2D textureWall1;
	//Texture2D textureWall2;

	Texture2D textureWindow1;
	//Texture2D textureWindow2;
	//Texture2D textureWindow3;
	//Texture2D textureWindow4;
	//Texture2D textureWindow5;
	//Texture2D textureWindow6;


public:
	Paralax(
		float velocityFloors,
		Texture2D textureFloor,
		Texture2D textureWall1,
		Texture2D textureWindow1);

	~Paralax();

	//draw
	void DrawParalax();

	void DrawFloor();
	void DrawWall();
	void DrawWindow();

	//update
	void UpdateParalax();

	void UpdateFloor();
	void UpdateWall();
	void UpdateWindow();

};



