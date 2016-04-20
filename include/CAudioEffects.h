#ifndef _AUDIO_EFFECTS
#define _AUDIO_EFFECTS

#include "CAudio.h"

//--------------------------------------------------------------------------------------
//
//	CAudio.h
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


/////////////////////////////
// Private data members
private:
	bool paused;

	// SFML variables
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	sf::Vector3f soundPos;
	sf::Vector3f soundVelocity;
	sf::Vector3f listenerPos;
	sf::Vector3f listenerForward;
	sf::Vector3f listenerUp;
};

#endif
