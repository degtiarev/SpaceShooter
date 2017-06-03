#pragma once

class FPS
{
public:
	FPS();
	~FPS();

	void CalculateFrameRate();
	float getCurrentTime();
	float getFPS();

private:
	double fps;
	float currentTime;
	float startTime;

};
