/*************************************************************\
 * Globals.h                                                 *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the declaration of the Globals class   *
 * which is little more than a struct to hold variables      *
 * that need to be accessed in many different places         *
\*************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "HeadsUpDisplay.h"
#include "CameraControl.h"
#include "PauseScreen.h"

class Globals
{
public:
	static bool
		clipping,
		goDim, goDark, loading,
		getInput, isPaused, isInScreen;

	static HeadsUpDisplay HUD;
	static CameraControl Cam;
	static PauseScreen pause;
	static std::string curr_level;
};

#endif