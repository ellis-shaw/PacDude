#ifndef _MENU_SELECTION
#define _MENU_SELECTION

#include "CAudio.h"

// See comment in CPP for issues with current style

// enumerators for menu options
enum Selection { Play, Mute, Quit };

// menu interaction
void MoveSelectionUp(BAudio* soundObject);
void MoveSelectionDown(BAudio* soundObject);

// debug code
int GetCurrentSelection();

#endif