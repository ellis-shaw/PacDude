#ifndef _AUDIO_EFFECTS
#define _AUDIO_EFFECTS

#define _MINI_GAME

#include <string>

// one for menu effects and the other for music
void LoadSoundFile(const std::string &fileName);
void PlaySoundFile();

// one for menu effects and the other for music
void PlaySoundTrackMenu();
void PlaySoundTrackInGame();

// one for menu effects and the other for music
void StopSoundTrackMenu();
void StopSoundTrackInGame();

// one for menu effects and the other for music
void PauseUnPauseSoundTrackMenu();
void PauseUnPauseSoundTrackInGame();

// unused class
class Audio
{
	Audio();	
};

#ifdef _MINI_GAME

// silly audio game thing. use space bar and the + and -

void LoadMiniSound();
void PlayMiniSound();
void IncrementPitch();
void DecrementPitch();
float ChangeSemitone(float frequency, float variation);
#endif

#endif