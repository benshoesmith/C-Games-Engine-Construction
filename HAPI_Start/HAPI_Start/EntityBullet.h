#pragma once
#include "Entity.h"
class EntityBullet :
	public Entity
{
private:
	float m_speed = 50.0f;


public:
	EntityBullet(std::string spriteName, int numFrames = 1);
	~EntityBullet();

	void Update() override final;

	void ResetToNewPosition();

	bool CheckCollision(Visualisation & viz, Entity & other);

	virtual ESide GetSide() const override final { return ESide::ePlayer; }


};

