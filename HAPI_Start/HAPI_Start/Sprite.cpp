#include "Sprite.h"

Sprite::Sprite(int m_numFrames)
{
	numFrames = m_numFrames;

}

Sprite::~Sprite()
{
	delete[] m_texturePnter;
}


bool Sprite::Load(const std::string& filename, int numFrames)
{
	int w, h;
	if (!HAPI.LoadTexture(filename, &m_texturePnter, w, h))
		return false;
	m_textureRect = Rectangle(w, h);
	m_frameRect = Rectangle(m_textureRect.Width() / numFrames, m_textureRect.Height());

	return true;
}

void Sprite::Render(const Rectangle& screenRect, BYTE* screen, int posX, int posY, int frameNum)
{

	//Create new rectangle
	Rectangle clippedRect(m_frameRect);

	//give rectangle position
	clippedRect.Translate(posX, posY);

	if (clippedRect.CompletelyOutside(screenRect))
		return;

	if (!clippedRect.CompletelyContains(screenRect))
	{
		clippedRect.ClipTo(screenRect);
	}

	//After clipping, give new position
	clippedRect.Translate(-posX, -posY);

	if (posX < 0) posX = 0;
	if (posY < 0) posY = 0;

	clippedRect.Translate(frameNum * m_frameRect.Width(), 0);

	BYTE *screenPnter = screen + (posX + posY * screenRect.Width()) * 4;
	BYTE *texturePnter = m_texturePnter + (clippedRect.left + clippedRect.top * m_textureRect.Width()) * 4;
	int endOfLineScreenIncrement = (screenRect.Width() - clippedRect.Width()) * 4;
	int endOfLineTextureIncrement = (m_textureRect.Width() - clippedRect.Width()) * 4;
	for (int y = 0; y < clippedRect.Height(); y++)
	{
		for (int x = 0; x < clippedRect.Width(); x++)
		{

			BYTE blue = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE red = texturePnter[2];
			BYTE alpha = texturePnter[3];

			float mod = alpha / 255.0f;
			screenPnter[0] = (BYTE)(mod * blue + (1.0f - mod) * screenPnter[0]);
			screenPnter[1] = (BYTE)(mod * green + (1.0f - mod) * screenPnter[1]);
			screenPnter[2] = (BYTE)(mod  *red + (1.0f - mod) * screenPnter[2]);

			screenPnter += 4;
			texturePnter += 4;
		}
		screenPnter += endOfLineScreenIncrement;
		texturePnter += endOfLineTextureIncrement;
	}

}