#include "CMusic.h"

CMusic::CMusic(const std::string& soundFile)
{
	// assuming sound file *Not music*	
	// check if file exists
	if (FileExists(soundFile))
	{
		// File sucessfully loaded
		std::cout << "Audio file loaded...\nFILE DIR: " << soundFile << "\n\n";

		// Manage SFML resources
		music.openFromFile(soundFile);

		music.setPosition(soundPos);

		music.setVolume(40); // 0 to 100

		// audio will loop
		music.setLoop(true);

		paused = false;
	}
	else
	{
		std::cerr << "ERROR: Cannot find audio file \nFILE DIR: " << soundFile << "\n\n";
	}
}

void CMusic::Stop()
{
	music.stop();
}

void CMusic::Play()
{
	music.play();
}

void CMusic::PauseUnPauseFile()
{
	if (paused)
	{
		paused = false;
		music.play();
	}
	else
	{
		paused = true;
		music.pause();
	}
}

void CMusic::IncreaseVolume(const int& amount)
{
	music.setVolume(music.getVolume() + amount);
}

void CMusic::DecreaseVolume(const int& amount)
{
	music.setVolume(music.getVolume() - amount);
}

void CMusic::IncreasePitch()
{
	float pitch = music.getPitch();

	if (pitch < 4.0f)
	{
		pitch = ChangeSemitone(pitch, 1.0f);
		music.setPitch(pitch);
	}
}

void CMusic::DecreasePitch()
{
	float pitch = music.getPitch();

	if (pitch > 0.117f)
	{
		pitch = ChangeSemitone(pitch, -1.0f);
		music.setPitch(pitch);
	}
}

void CMusic::IncreasePitch(const int& amount)
{
	float pitch = music.getPitch();

	if (pitch < 4.0f)
	{
		pitch = ChangeSemitone(pitch, amount);
		music.setPitch(pitch);
	}
}

void CMusic::DecreasePitch(const int& amount)
{
	float pitch = music.getPitch();

	if (pitch > 0.117f)
	{
		pitch = ChangeSemitone(pitch, amount);
		music.setPitch(pitch);
	}
}
