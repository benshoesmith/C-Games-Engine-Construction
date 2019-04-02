#include "EntityBackground.h"

EntityBackground::EntityBackground(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}

EntityBackground::~EntityBackground()
{
}

void EntityBackground::Update()
{
	Vector2 pos(GetPosition());

	pos.y += m_speed;

	if (pos.y >= 0)
	{
		pos.y = -1400;
		SetPosition(pos);
	}

	SetPosition(pos);
}
