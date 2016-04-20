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

		sound.setVolume(40.0f); // 0 to 100
		sound.setPitch(4.0f);
		sound.setLoop(false);
		sound.setPosition(soundPos);

		// setting up sound position
		soundPos.x = 0.0;
		soundPos.y = 0.0;
		soundPos.z = 0.0;

		// setting up sound velocity
		soundVelocity.x = 0.0;
		soundVelocity.y = 0.0;
		soundVelocity.z = 0.0;

		// setting up lister position
		listenerPos.x = 0.0;
		listenerPos.y = 0.0;
		listenerPos.z = 0.0;

		// setting up listener forward
		listenerForward.x = 0.0;
		listenerForward.y = 0.0;
		listenerForward.z = -1.0;

		// setting up listener up
		listenerUp.x = 0.0;
		listenerUp.y = 1.0;
		listenerUp.z = 0.0;

		// 0 to 100
		sf::Listener::setGlobalVolume(100.0f);
		sf::Listener::setPosition(listenerPos);
		sf::Listener::setDirection(listenerForward);
		sf::Listener::setUpVector(listenerUp);

		// audio won't loop
		sound.setLoop(false);
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
