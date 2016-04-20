#include "CAudio.h"

BAudio::BAudio()
{
}

bool BAudio::FileExists(const std::string& soundFile)
{
	std::ifstream infile(soundFile);
	return	 infile.good();
}

float BAudio::ChangeSemitone(float frequency, float variation)
{
	static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
	return frequency * pow(semitone_ratio, variation);
}

float Timer()
{
	static clock_t currTime = clock();
	clock_t prevTime = currTime;
	currTime = clock();
	return float(currTime - prevTime) / CLOCKS_PER_SEC;
}