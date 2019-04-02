#include "Visualisation.h"
#include "Sprite.h"


Visualisation::Visualisation()
{
}


Visualisation::~Visualisation()
{
	for (auto& p : m_spriteMap)
		delete p.second;
}

bool Visualisation::Initialise(int width, int height)
{
	if (!HAPI.Initialise(width, height, "GEC ICA 2"))
	{
		std::cerr << "Couldn't Initialise" << std::endl;
		return false;
	}
		

	m_screenRect = Rectangle(width, height);

	m_screenPnter = HAPI.GetScreenPointer();

	return true;
}
void Visualisation::ClearToGrayscale(BYTE gray)
{
	memset(m_screenPnter, gray, m_screenRect.Width()*m_screenRect.Height() * 4);
}

 void Visualisation::ClearToColour(HAPI_TColour colour)
{
	for (int y = 0; y < m_screenRect.Height(); y++)
	{
		for (int x = 0; x < m_screenRect.Width(); x++)
		{
			int offset = (x + y * m_screenRect.Width()) * 4;
			m_screenPnter[offset] = colour.red; //r
			m_screenPnter[offset + 1] = colour.green; //g
			m_screenPnter[offset + 2] = colour.blue; //b
		}
	}
}

 bool Visualisation::CreateSprite(const std::string& name, const std::string& filename, int numFrames) {

	 Sprite * newSprite = new Sprite(numFrames);
	 if (!newSprite->Load(filename, numFrames))
		 return false;

	 m_spriteMap.insert({ name, newSprite });

	 return true;

 }

 void Visualisation::RenderSprite(const std::string& name, int posX, int posY, int frameNum) const {

	 m_spriteMap.find(name)->second->Render(m_screenRect, m_screenPnter, posX, posY, frameNum);

 }