/*************************************************************\
 * GameManager.h                                             *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the declaration of the GameManger class*
 * Which oversees and manages the flow of the game           *
\*************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//****** LIBRARIES AND CLASSES ******\\

// For the keyboard functionality
#include "Keyboard.h"

// glut really wants cstdlib here
#include <cstdlib>

// For arrays of strings
#include <string>
#include <vector>

// OpenGL API
#include <GL\glut.h>

// Standard I/O for debugging
#include <iostream>

// To manage background music
#include "MusicManager.h"

// To manage saving and loading
#include "SaveManager.h"

class GameManager
{
private:
	// Variables

	// Objects
	MusicManager SoundSystem;
	Keyboard board;

	// Because the main menu is dumb, we have to know when to get a click
	bool processClick = false;

	// When in the main menu, mouse coords of a click
	int mouse_x, mouse_y;

	// Functions

public:

	// Captures mouse clicks
	void mouse(int button, int state, int x, int y);
	// Captures mouse motion
	void motionPassive(int x, int y);
	// CHanges window size
	void changeSize(int w, int h);
	// Manages scene display
	void manageScenes();
	// Displaying function
	void draw();
	// Function to bring about game end on Level 4
	void endGame();
	// Normal key presses
	void normal(unsigned char key, int x, int y);
	// Key releases
	void key_up(unsigned char key, int x, int y);
	// Special keys
	void special(int key, int x, int y);
	// To manage playing and releasing music
	void manageMusic();

	// Wether or not core.sav exists
	bool canContinue;

};

#endif