/*************************************************************\
 * MusicManager.cpp                                          *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the definition of the MusicManager     *
 * Class. For more information, see MusicManager.h           *
\*************************************************************/

// Class definition
#include "MusicManager.h"

// Because concatenating char*'s are really hard
#include <string>

// Return codes
#include "Return.h"

// System log
#include "Logger.h"

using namespace std;

// Initialize the constant member of the class
const char* MusicManager::MUSIC_PATH = "Resources\\Music\\";

MusicManager::MusicManager()
{
	Logger log;
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		log.logLine("FATAL ERROR: FMOD unable to create system");
		exit(FMOD_ERROR);
	}

	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);

	// If you have no driver, you have bigger problems to worry about
	if (driverCount == 0)
	{
		// Report Error
		log.logLine("ERROR: FMOD unable to detect drivers");
		exit(FMOD_ERROR);
	}

	log.logLine("FMOD succesfully initialized");
	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}

void MusicManager::makeSound(SoundClass *psound, const char *song)
{
	// MUSIC_PATH is placed in a nice string. Good string. Strings are friends
	string fullPath = MUSIC_PATH;
	// Now there is a full path to the song
	fullPath += song;

	m_pSystem->createSound(fullPath.c_str(), FMOD_DEFAULT, 0, psound);
}

void MusicManager::playSound(SoundClass pSound, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	m_pSystem->playSound(pSound, NULL , false, 0);
}

void MusicManager::releaseSound(SoundClass pSound)
{
	pSound->release();
}