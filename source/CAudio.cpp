#include "CAudio.h"

BAudio::BAudio()
{
}

bool BAudio::FileExists(const std::string& soundFile)
{
	std::ifstream infile(soundFile);
	return	 infile.good();
}

float Timer()
{
	static clock_t currTime = clock();
	clock_t prevTime = currTime;
	currTime = clock();
	return float(currTime - prevTime) / CLOCKS_PER_SEC;
}

//#ifdef  _MINI_GAME
//
//sf::SoundBuffer bufferMini;
//sf::Sound soundMini;
//float pitch = 1.0f;
//
//#endif

//#ifdef _MINI_GAME
//void LoadMiniSound()
//{
//	if (!bufferMini.loadFromFile(".\\AudioFiles\\synthOneShot.wav"))
//	{
//		std::cout << "Error loading sound file" << std::endl;
//		while (!_kbhit());
//		return;
//	}
//
//	soundMini.setBuffer(bufferMini);
//
//	// Set the properties of the source. Details of all available properties are in the SFML documentation of the Sound class
//	soundMini.setVolume(40.0f); // 0 to 100
//	soundMini.setPitch(pitch);
//	soundMini.setLoop(false);
//	soundMini.setPosition(0.0, 0.0, 0.0);
//}
//
//void PlayMiniSound()
//{
//	soundMini.play();
//}
//
//void IncrementPitch()
//{
//	if (pitch < 4.0f)
//	{
//		pitch = ChangeSemitone(pitch, 1.0f);
//		soundMini.setPitch(pitch);
//	}	
//}
//
//void DecrementPitch()
//{
//	if (pitch > 0.117f)
//	{
//		pitch = ChangeSemitone(pitch, -1.0f);
//		soundMini.setPitch(pitch);
//	}	
//}
//
//float ChangeSemitone(float frequency, float variation)
//{
//	static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
//	return frequency * pow(semitone_ratio, variation);
//}
//
//#endif