#include "CAudioEffects.h"

CAudioEffects::CAudioEffects(const std::string& soundFile)
{
	// assuming sound file *Not music*	
	// check if file exists
	if (FileExists(soundFile))
	{
		// File sucessfully loaded
		std::cout << "Audio file loaded...\nFILE DIR: " << soundFile << "\n\n";

		// Manage SFML resources
		buffer.loadFromFile(soundFile);
		sound.setBuffer(buffer);

		sound.setVolume(100); // 0 to 100
		sound.setPosition(soundPos);

		// audio won't loop
		sound.setLoop(false);

		paused = false;
	}
	else
	{
		std::cerr << "ERROR: Cannot find audio file \nFILE DIR: " << soundFile << "\n\n";
	}
}

void CAudioEffects::Stop()
{
	
}

void CAudioEffects::Play()
{
	sound.play();
}

void CAudioEffects::PauseUnPauseFile()
{
	if (paused)
	{
		paused = false;
		sound.play();
	}
	else
	{
		paused = true;
		sound.pause();
	}
}

void CAudioEffects::IncreaseVolume(const int &amount)
{
	sound.setVolume(sound.getVolume() + amount);
}

void CAudioEffects::DecreaseVolume(const int &amount)
{
	sound.setVolume(sound.getVolume() - amount);
}

void CAudioEffects::IncreasePitch()
{
	float pitch = sound.getPitch();

	if (pitch < 4.0f)
	{
		pitch = ChangeSemitone(pitch, 1.0f);
		sound.setPitch(pitch);
	}
}

void CAudioEffects::DecreasePitch()
{
	float pitch = sound.getPitch();

	if (pitch > 0.117f)
	{
		pitch = ChangeSemitone(pitch, -1.0f);
		sound.setPitch(pitch);
	}
}

void CAudioEffects::IncreasePitch(const int & amount)
{
	float pitch = sound.getPitch();

	if (pitch < 4.0f)
	{
		pitch = ChangeSemitone(pitch, amount);
		sound.setPitch(pitch);
	}
}

void CAudioEffects::DecreasePitch(const int& amount)
{
	float pitch = sound.getPitch();

	if (pitch > 0.117f)
	{
		pitch = ChangeSemitone(pitch, amount);
		sound.setPitch(pitch);
	}
}
