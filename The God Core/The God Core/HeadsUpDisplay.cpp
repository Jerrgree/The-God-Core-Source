/*************************************************************\
 * HeadsUpDisplay.cpp                                        *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the definition of the HeadsUpDisplay   *
 * Class. For more information, see HeadsUpDisplay.h         *
\*************************************************************/

// Class Declaration
#include "HeadsUpDisplay.h"

// OpenGL API
#include <gl\glut.h>

// For counting seconds
#include <ctime>

// For displaying Planes
#include "Plane.h"

// For displaying triangles
#include "Triangle.h"

using namespace std;

void HeadsUpDisplay::drawHelmetBounds()
{
	// Helmet bounds are black
	double colors[4] = { 0, 0, 0, 1 };

	// The top of the helmet
	double top_vertices[9] =
	{
		SCREENRIGHT, SCREENTOP, -1,
		SCREENLEFT, SCREENTOP, -1,
		SCREENRIGHT / 2.0, SCREENBOTTOM / 20.0, -1
	};

	// The left of the hemlet
	double left_vertices[9] =
	{
		SCREENLEFT, SCREENBOTTOM, -1,
		SCREENLEFT, SCREENTOP, -1,
		SCREENRIGHT / 20.0, 3 * SCREENBOTTOM / 5.0, -1
	};

	// The back of the helmet
	double right_vertices[9] =
	{
		SCREENRIGHT, SCREENBOTTOM, -1,
		SCREENRIGHT, SCREENTOP, -1,
		19 * SCREENRIGHT / 20.0, 3 * SCREENBOTTOM / 5.0, -1
	};

	Triangle top_helm{ top_vertices, colors };
	Triangle left_helm{ left_vertices, colors };
	Triangle right_helm{ right_vertices, colors };

	top_helm.Display2D();
	left_helm.Display2D();
	right_helm.Display2D();
}

void HeadsUpDisplay::DisplayAlerts()
{
	helmet.openFile(.5 * SCREENRIGHT, .5 * SCREENBOTTOM,
		1, 1, 1,
		"suitAlerts.log", currentAlert);
}

void HeadsUpDisplay::dim()
{
	static int startTime;
	static bool timeSet = false;
	if (dimNow)
	{
		if (!timeSet)
		{
			startTime = time(NULL);
			timeSet = true;
		}

		int currentTime = time(NULL);
		int timeElapsed = currentTime - startTime;
		if (timeElapsed < dimTime)
		{
			// A black square that grows more transparent as time passes
			double colors[4] = { 0, 0, 0, (double)(dimTime - timeElapsed) / dimTime };
			double dimVert[12] =
			{
				SCREENLEFT, SCREENTOP, -1,
				SCREENLEFT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENTOP, -1
			};

			Plane black{ dimVert, colors };
			black.Display2D();
		}

		else
		{
			dimNow = false;
			timeSet = false;
		}
	}
}

void HeadsUpDisplay::fade()
{
	static int startTime;
	static bool timeSet = false;
	if (fadeNow)
	{
		if (!timeSet)
		{
			startTime = time(NULL);
			timeSet = true;
		}

		int currentTime = time(NULL);
		int timeElapsed = currentTime - startTime;
		if (timeElapsed < fadeTime)
		{
			// A black square that grows more transparent as time passes
			double colors[4] = { 0, 0, 0, 1 - ((double)(fadeTime - timeElapsed) / fadeTime) };
			double dimVert[12] =
			{
				SCREENLEFT, SCREENTOP, -1,
				SCREENLEFT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENTOP, -1
			};

			Plane black{ dimVert, colors };
			black.Display2D();
		}

		else
		{
			fadeNow = false;
			timeSet = false;


			// Go dark till game ends
			darkNow = true;
			darkTime = 1000;
		}
	}
}

void HeadsUpDisplay::dark()
{
	static int startTime;
	static bool timeSet = false;
	if (darkNow)
	{
		if (!timeSet)
		{
			startTime = time(NULL);
			timeSet = true;
		}

		int currentTime = time(NULL);
		int timeElapsed = currentTime - startTime;
		if (timeElapsed < darkTime)
		{
			// A black square that obscures vision
			double colors[4] = { 0, 0, 0, 1 };
			double dimVert[12] =
			{
				SCREENLEFT, SCREENTOP, -1,
				SCREENLEFT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENBOTTOM, -1,
				SCREENRIGHT, SCREENTOP, -1
			};

			Plane black{ dimVert, colors };
			black.Display2D();
		}

		else
		{
			darkNow = false;
			timeSet = false;
		}
	}
}

void HeadsUpDisplay::drawConsole()
{
	double colors[4] = { .1, .1, .1, .9 };
	double vertices[12] =
	{
		SCREENLEFT, SCREENTOP, -1,
		SCREENLEFT, SCREENBOTTOM / 5, -1,
		SCREENRIGHT, SCREENBOTTOM / 5, -1,
		SCREENRIGHT, SCREENTOP, -1
	};

	Plane console_tab{ vertices, colors };
	console_tab.Display2D();	

	if (currentInput != "")
	{
		dev.activate(currentInput, currentText);
		currentInput.clear();
	}

	else
	{
		dev.activate(currentText);
	}
}

void HeadsUpDisplay::drawInfoBox()
{
	double colors[4] = { 0, 1, 1, .5 };
	double vertices[12] =
	{
		SCREENLEFT, SCREENTOP, -1,
		SCREENLEFT, SCREENBOTTOM / 10, -1,
		SCREENRIGHT / 10, SCREENBOTTOM / 10, -1,
		SCREENRIGHT / 10, SCREENTOP, -1
	};

	Plane info{ vertices, colors };
	info.Display2D();
}

void HeadsUpDisplay::displayInfo(string tag)
{
	helmet.openFile(SCREENLEFT, SCREENTOP +  20, 1, 1, 1,
		"suitAlerts.log", currentStatus);
}

void HeadsUpDisplay::goDim(int time)
{
	dimTime = time;
	dimNow = true;
}

void HeadsUpDisplay::goDark(int time)
{
	darkTime = time;
	darkNow = true;
}

void HeadsUpDisplay::goFade(int time)
{
	fadeTime = time;
	fadeNow = true;
}

void HeadsUpDisplay::displayWarning(std::string warning)
{
	currentAlert = warning;
}

void HeadsUpDisplay::setStatus(std::string status)
{
	currentStatus = status;
}

void HeadsUpDisplay::printToConsole(std::string text)
{
	currentText = text;
}

void HeadsUpDisplay::inputString(std::string text)
{
	currentInput = text;
}

void HeadsUpDisplay::toggleConsole()
{
	devConsole = !devConsole;
}

void HeadsUpDisplay::drawHUD()
{
	drawHelmetBounds();

	if (dimNow)
	{
		dim();
	}

	else if (fadeNow)
	{
		fade();
	}

	// Not else if due to fade -> dark transition
	if (darkNow)
	{
		dark();
	}

	drawInfoBox();
	displayInfo(currentStatus);

	if (devConsole)
	{
		drawConsole();
	}

	if (currentAlert != "")
	{
		DisplayAlerts();
	}
}

string HeadsUpDisplay::getHist(int count)
{
	return dev.getHist(count);
}

int HeadsUpDisplay::getHistNum()
{
	return dev.getHistNum();
}

void HeadsUpDisplay::DisplayHUD()
{
	prepare2D();

	drawHUD();

	prepare3D();
}