#include "Timer.h"

Timer::Timer(float timerEnd)
{
	this->timerPass = 0;
	this->timerEnd = timerEnd;
	this->IsEnded = false;
	this->IsPaused = false;
}

Timer::~Timer()
{

}

void Timer::AddTime(float addTime)
{
	if (!IsPaused)
	{
		timerPass += addTime;
	}
}

bool Timer::GetIsTimeEnd()
{
	return IsEnded;
}

void Timer::SetIsPaused(bool setPause)
{
	IsPaused = setPause;
}

bool Timer::GetIsPaused()
{
	return 
}