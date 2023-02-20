#pragma once
#include "raylib.h"

using namespace std;

namespace Game
{
	class Paralax
	{
	private:
		float positionFloorY;
		float ScrollingFloor;
		float velocityFloors;

		float positionWallY;
		float ScrollingWall1;
		float ScrollingWall2;
		float velocityWalls;

		int tipeWindow;
		Vector2 positionWindow;
		float velocityWindow;


		Texture2D textureFloor;

		Texture2D textureWall1;
		Texture2D textureWall2;

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
			Texture2D textureWall2,
			Texture2D textureWindow1);

		~Paralax();

		//draw
		void DrawParalax();

		void DrawFloor();
		void DrawWall();
		void DrawWindow();

		//update
		void UpdateParalax(float velocityObstacles);

		void UpdateFloor();
		void UpdateWall();
		void UpdateWindow();

	};
}