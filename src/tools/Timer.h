#pragma once

class Timer
{
private:
	float timerPass;
	float timerEnd;
	bool IsEnded;

public:
	Timer(float timerEnd);
	~Timer();
	void AddTime(float addTime);
	bool IsTimeEnd();
};

