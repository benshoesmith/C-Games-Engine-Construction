#pragma once
#include "Entity.h"
class EntityBackground :
	public Entity
{
private:
	float m_speed = 5.0f;
public:
	EntityBackground(std::string spriteName, int numFrames = 1);
	~EntityBackground();

	void Update() override final;

	virtual ESide GetSide() const override final { return ESide::eNeutral; }
};

