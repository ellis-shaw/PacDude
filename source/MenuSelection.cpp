#include "MenuSelection.h"

Selection selection = Play;			// initial start position for menu
static const int menuAmount = 1;	// amount of menu options -1.
int counter = 0;					// keeps track of selection value

void MoveSelectionUp(BAudio* soundObject)
{
	if (counter > 0)
	{
		counter--;

		// cast enum to int, since you cant do treat like int for some reason
		// even tho enums can be treated like ints anyway
		selection = static_cast<Selection>(counter);

		// hide away the audio calls, so that you cant create sound even
		// when not moving in menu UI
		if(soundObject != nullptr)
			soundObject->Play();
	}
}

void MoveSelectionDown(BAudio* soundObject)
{
	if (counter < menuAmount)
	{
		counter++;
		
		// cast enum to int, since you cant do treat like int for some reason
		// even tho enums can be treated like ints anyway
		selection = static_cast<Selection>(counter);

		// hide away the audio calls, so that you cant create sound even
		// when not moving in menu UI
		if (soundObject != nullptr)
			soundObject->Play();
	}
}

// functions return values based on item in enum, useful for debugging purposes

int GetCurrentSelection()
{
	return selection;
}