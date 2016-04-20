#ifndef _AUDIO_EFFECTS
#define _AUDIO_EFFECTS

#include "CAudio.h"

//--------------------------------------------------------------------------------------
//
//	CAudioEffects.h
//
//	Handles audio effects
//
//--------------------------------------------------------------------------------------

class CAudioEffects : public BAudio
{
/////////////////////////////
// Public member functions
public:
	CAudioEffects(const std::string &soundFile);

	virtual ~CAudioEffects() {};

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
	sf::Sound sound;
	sf::Vector3f soundPos;
	sf::Vector3f soundVelocity;
	sf::Vector3f listenerPos;
	sf::Vector3f listenerForward;
	sf::Vector3f listenerUp;
};

#endif
