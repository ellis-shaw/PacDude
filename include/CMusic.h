#ifndef _AUDIO_MUSIC
#define _AUDIO_MUSIC

#include "CAudio.h"

//--------------------------------------------------------------------------------------
//
//	CMusic.h
//
//	Handles music
//
//--------------------------------------------------------------------------------------

class CMusic : public BAudio
{
	
/////////////////////////////
// Public member functions
public:
	CMusic(const std::string &soundFile);

	virtual ~CMusic() {};

	// play sound file
	void Play();

	// stop sound file
	void Stop();

	// pause depending if playing
	void PauseUnPauseFile();

	// increase volume
	void IncreaseVolume(const int &amount);

	// decrease volume
	void DecreaseVolume(const int &amount);

	// increase pitch
	void IncreasePitch();

	// decrease pitch
	void DecreasePitch();

	// increase pitch
	void IncreasePitch(const int &amount);

	// decrease pitch
	void DecreasePitch(const int &amount);


/////////////////////////////
// Private data members
private:
	bool paused;

	// SFML variables
	sf::SoundBuffer buffer;
	sf::Music music;
	sf::Vector3f soundPos;
	sf::Vector3f soundVelocity;
	sf::Vector3f listenerPos;
	sf::Vector3f listenerForward;
	sf::Vector3f listenerUp;
};
#endif
