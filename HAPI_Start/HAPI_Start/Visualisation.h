#pragma once

#include <HAPI_lib.h>
#include "Rectangle.h"
#include <string>
#include <unordered_map>

using namespace HAPISPACE;

class Sprite;
class Visualisation
{
private:
	
	Rectangle m_screenRect;
	BYTE *m_screenPnter{ nullptr };

public:
	std::unordered_map<std::string, Sprite*> m_spriteMap;
	Visualisation();
	~Visualisation();

	bool Initialise(int width, int height);
	void ClearToGrayscale(BYTE gray);
	void ClearToColour(HAPI_TColour colour);
	bool CreateSprite(const std::string& name, const std::string& filename, int numFrames = 1);
	void RenderSprite(const std::string& name, int posX, int posY, int frameNum = 0) const;
};

