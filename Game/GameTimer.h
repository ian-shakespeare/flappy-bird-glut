#pragma once

#include <ctime>

class GameTimer
{
private:
	unsigned int frames = 0;
	double seconds = 0;
	double frames_per_second;
public:
	GameTimer();
	void Update();
	unsigned int GetGameFrames();
	double GetGameTime();
};

