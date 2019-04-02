#pragma once
#include "Entity.h"
class EntityEnemy :
	public Entity
{

private:
	float m_speed = 10.0f;//Movement speed

public:
	EntityEnemy(std::string spriteName, int numFrames = 1);
	~EntityEnemy();

	void Update() override final;
	void ResetToNewPosition();

	int enemyIncrement = 1;

	virtual ESide GetSide() const override final { return ESide::eEnemy; }

};

