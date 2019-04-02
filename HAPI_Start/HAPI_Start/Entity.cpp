#include "Entity.h"
#include "Visualisation.h"
#include "Sprite.h"


Entity::Entity(std::string spriteName, int numFrames) : m_spriteName(spriteName), m_numFrames(numFrames)
{
}


Entity::~Entity()
{
}

void Entity::Render(Visualisation &viz, float s)
{
	if (!m_alive)
		return;

	Vector2 interPos{ m_oldPosition + (m_position - m_oldPosition) * s };

	viz.RenderSprite(m_spriteName, (int)interPos.x, (int)interPos.y, m_frameNum);

	if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime)
	{
		m_frameNum++;
		if (m_frameNum >= m_numFrames)
			m_frameNum = 0;
		m_lastTimeUpdatedAnimation = HAPI.GetTime();
	}
}

void Entity::ResetToNewPosition()
{
}

bool Entity::CheckCollision(Visualisation & viz, Entity & other) {
	return false;
}
