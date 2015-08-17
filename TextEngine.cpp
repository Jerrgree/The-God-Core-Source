/*************************************************************\
 * TextEngine.cpp                                            *
 * This file was created by Jeremy Greenburg                 *
 * As part of The God Core game for the University of        *
 * Tennessee at Martin's University Scholars Organization    *
 *                                                           *
 * This file contains the definition of the TextEngine class *
 * For more information, see TextEngine.h                    *
\*************************************************************/

// TextEngine declaration and std::string
#include "TextEngine.h"

// std::ifstream
#include <fstream>

// Standard I/O for debugging
#include <iostream>

// OpenGL API
#include <gl\glew.h>
#include <gl\glut.h>

using namespace std;

// Initializing the constants
const char* TextEngine::TEXT_PATH = "Resources\\Scripts\\";
const char* TextEngine::SAVE_PATH = "Resources\\Save Data\\";
const float TextEngine::LINE_OFFSET = 10;

void TextEngine::displayText(float x, float y,
	float r, float g, float b,
	void* font, vector<string> text)
{
	vector<string>::iterator it;

	// Iterates throguh the text vector and prints it to the screen
	for (it = text.begin(); it != text.end(); it++)
	{
		glColor3f(r, g, b);
		glRasterPos2f(x, y);

		for (unsigned int i = 0; i < it->length(); i++)
		{
			glutBitmapCharacter(font, (*it)[i]);
		}

		// Because glut does not print newlines
		y += LINE_OFFSET;
	}
}

vector<string> TextEngine::findText(string fileName, string tag)
{
	// The tags are listed between dollar signs
	string fullTag = '$' + tag + '$';

	string fullPath = TEXT_PATH + fileName;

	ifstream infile(fullPath);

	// Buffer to read in data
	string buff;
	// Array to store strings
	vector<string> data;

	// Find the string(s) to read in
	getline(infile, buff);
	while (infile && buff != fullTag)
	{
		getline(infile, buff);
	}

	// Store the string(s)
	getline(infile, buff);
	while (infile && buff != "$END$")
	{
		data.push_back(buff);
		getline(infile, buff);
	}

	infile.close();

	return data;
}

void TextEngine::openFile(float x, float y,
	float r, float g, float b,
	string fileName, string tag)
{
	vector<string> input = findText(fileName, tag);

	displayText(x, y, r, g, b,
		GLUT_BITMAP_HELVETICA_12,
		input);
}

vector<string> TextEngine::getText(string fileName, string tag)
{
	vector<string> input = findText(fileName, tag);

	return input;
}

void TextEngine::printString(float x, float y, float r, float g, float b,
	string text)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);

	for (unsigned int i = 0; i < text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}

	// Vertical spacing
	y += LINE_OFFSET;
}