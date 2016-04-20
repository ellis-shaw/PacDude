#include "MenuSelection.h"
#include "AudioEffects.h"

/*
ERROR OCCURS IF YOU HAVE MORE THAN TWO SELECTIONS
TO REPLICATE THE BEHAVIOUR FOR MORE OPTIONS IMPLEMENT
A COUNTER I.E. DOWN DECREMENTS, UNTIL IT REACHES LIMIT AND RESETS
SAME BEHAVIOUR IN THE OPPOSITE DIRECTION FOR UP
*/

Selection selection = Play;			// initial start position for menu
static const int menuAmount = 1;	// amount of menu options -1.
int counter = 0;					// keeps track of selection value

void MoveSelectionUp()
{
	if (counter > 0)
	{
		counter--;

		// cast enum to int, since you cant do treat like int for some reason
		// even tho enums can be treated like ints anyway
		selection = static_cast<Selection>(counter);

		// hide away the audio calls, so that you cant create sound even
		// when not moving in menu UI
		//PlaySoundFile();
	}
}

void MoveSelectionDown()
{
	if (counter < menuAmount)
	{
		counter++;
		
		// cast enum to int, since you cant do treat like int for some reason
		// even tho enums can be treated like ints anyway
		selection = static_cast<Selection>(counter);

		// hide away the audio calls, so that you cant create sound even
		// when not moving in menu UI
		//PlaySoundFile();
	}
}

// functions return values based on item in enum, useful for debugging purposes

int GetCurrentSelection()
{
	return selection;
}