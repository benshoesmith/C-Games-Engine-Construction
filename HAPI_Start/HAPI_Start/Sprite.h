#pragma once

#include <HAPI_lib.h>
using namespace HAPISPACE;
#include "Rectangle.h"

class Sprite
{
public:
	BYTE* m_texturePnter{ nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;
	int numFrames{ 1 };

public:
	Sprite(int m_numFrames);
	~Sprite();

	bool Load(const std::string& filename, int numFrames = 1);
	void Render(const Rectangle& screenRect, BYTE* screen, int posX, int posY, int frameNum = 0);
};

