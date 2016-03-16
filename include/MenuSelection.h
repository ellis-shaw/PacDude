#ifndef _MENU_SELECTION
#define _MENU_SELECTION

// See comment in CPP for issues with current style

// enumerators for menu options
enum Selection { Play, Mute, Quit };

// menu interaction
void MoveSelectionUp();
void MoveSelectionDown();

// debug code
int GetCurrentSelection();

#endif