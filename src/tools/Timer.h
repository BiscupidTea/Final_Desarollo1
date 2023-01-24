#pragma once

class Timer
{
private:
	float timerPass;
	float timerEnd;
	bool IsEnded;
	bool IsPaused;

public:
	Timer(float timerEnd);
	~Timer();
	void AddTime(float addTime);
	bool GetIsTimeEnd();

	void SetIsPaused(bool setPause);
	bool GetIsPaused();

	void RestartTimer();
};

