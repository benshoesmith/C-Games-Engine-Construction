#include "EntityEnemy.h"
#include<stdlib.h>
#include<time.h>


EntityEnemy::EntityEnemy(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::Update()
{
	Vector2 pos(GetPosition());
	//chickens move on y axis
	pos.y += m_speed;
	SetPosition(pos);

	//if chicken goes off map, reset position
	if (pos.y > 900)
	{
		ResetToNewPosition();
	}
}

void EntityEnemy::ResetToNewPosition()
{
	Vector2 pos2(GetPosition());
	//makes random position for chickens to spawn
	int randomPositionX = 10 + rand() % (690 - 10);
	int randomPositionY = (100 + rand() % (600 - 100)) * -1;
	pos2.x = (float)randomPositionX;
	pos2.y = (float)randomPositionY;
	//call setpos twice to avoid bad visuals
	SetPosition(pos2);
	SetPosition(pos2);

}

