#pragma once
#include "Entity.h"
class EntityPlayer :
	public Entity
{
private:
	float m_speed = 10.0f;

public:
	EntityPlayer(std::string spriteName, int numFrames = 1);
	~EntityPlayer();


	void Update() override final;

	bool CheckCollision(Visualisation & viz, Entity & other);

	void ResetToNewPosition();

	virtual ESide GetSide() const override final { return ESide::ePlayer; }
};

