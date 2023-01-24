#include "Timer.h"

Timer::Timer(float timerEnd)
{
	this->timerPass = 0;
	this->timerEnd = timerEnd;
	this->IsEnded = false;
}

Timer::~Timer()
{

}

void Timer::AddTime(float addTime)
{
	timerPass += addTime;
}

bool Timer::IsTimeEnd()
{
	return IsEnded;
}