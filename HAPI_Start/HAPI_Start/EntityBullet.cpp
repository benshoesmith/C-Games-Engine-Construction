#include "EntityBullet.h"
#include "Visualisation.h"
#include "Sprite.h"


EntityBullet::EntityBullet(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


EntityBullet::~EntityBullet()
{
}


void EntityBullet::Update()
{
	//static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	Vector2 pos(GetPosition());

	//if (keyData.scanCode[HK_UP])
	//{
	//	pos.y -= m_speed;
	//	m_isFired = true;
	//}


	if (m_isFired == true)
	{
		pos.y -= m_speed;

		SetPosition(pos);

		if (pos.y <= -60)
		{
			ResetToNewPosition();

		}

	}

}

void EntityBullet::ResetToNewPosition()
{
	Vector2 pos(GetPosition());

	pos.y = -100;
	pos.x = -100;
	m_isFired = false;

	SetPosition(pos);
	SetPosition(pos);

}

bool EntityBullet::CheckCollision(Visualisation & viz, Entity & other)
{

	Sprite* laser = viz.m_spriteMap.find(m_spriteName)->second;

	Rectangle laserRectangle = laser->m_frameRect;

	Vector2 laserPos = GetPosition();

	laserRectangle.Translate(laserPos.x, laserPos.y);

	laserRectangle.ReduceRectangleSize(10); //Reduce size to suit collision in %


	Sprite* comparedSprite = viz.m_spriteMap.find(other.GetName())->second;

	Rectangle comparedRectangle = comparedSprite->m_frameRect;

	Vector2 comparedPos = other.GetPosition();

	comparedRectangle.Translate(comparedPos.x, comparedPos.y);

	comparedRectangle.ReduceRectangleSize(20); //Reduce size to suit collision in %

	if (laserRectangle.CompletelyOutside(comparedRectangle) == false)
	{
		other.ResetToNewPosition();
		ResetToNewPosition();


		return true;
	}

	return false;

}