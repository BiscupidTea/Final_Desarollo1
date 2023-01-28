#pragma once
#include "tools/tools.h"

#include "Entity.h"

class Player : public Entity
{
private:
	int points;
	float distanceMade;
	bool alive;
	bool ground;
	bool jump;

public:
	Player(
		Vector2 position, Vector2 velocity,
		int width, int height, 
		float distanceMade, int points,
		bool alive);

	~Player();

	void Draw();

	void Movement();

	void IsPlayerGround();

	void Input(bool& isPaused);

	bool IsAlive();
	void SetIsAlive(bool aliveState);

	int GetPoints();
	void AddPoint(int sumPoints);

	float GetDistanceMade();
	void AddDistanceMade(float sumDistance);
};