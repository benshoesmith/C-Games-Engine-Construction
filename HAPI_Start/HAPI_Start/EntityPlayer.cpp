#include "EntityPlayer.h"
#include <HAPI_lib.h>
#include "Visualisation.h"
#include "Sprite.h"

using namespace HAPISPACE;

EntityPlayer::EntityPlayer(std::string spriteName, int numFrames) : Entity(spriteName, numFrames)
{
}


EntityPlayer::~EntityPlayer()
{
}


void EntityPlayer::Update()
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	Vector2 pos(GetPosition());
	//Controls
	if (keyData.scanCode[HK_DOWN])
		pos.y += m_speed;
	if (keyData.scanCode[HK_UP])
		pos.y -= m_speed;
	if (keyData.scanCode[HK_LEFT])
		pos.x -= m_speed;
	if (keyData.scanCode[HK_RIGHT])
		pos.x += m_speed;

	//Clamp player position to game
	if (pos.x <= 0)
	{
		pos.x = 0;
	}
	if (pos.x >= 595)
	{
		pos.x = 585;
	}
	if (pos.y <= 0)
	{
		pos.y = 0;
	}
	if (pos.y >= 695)
	{
		pos.y = 685;
	}

	SetPosition(pos);
}

bool EntityPlayer::CheckCollision(Visualisation & viz, Entity & other)
{

	Sprite* player = viz.m_spriteMap.find(m_spriteName)->second;
	Rectangle playerRectangle = player->m_frameRect;
	Vector2 playerPos = GetPosition();
	playerRectangle.Translate(playerPos.x, playerPos.y);


	Sprite* comparedSprite = viz.m_spriteMap.find(other.GetName())->second;
	Rectangle comparedRectangle = comparedSprite->m_frameRect;
	Vector2 comparedPos = other.GetPosition();
	comparedRectangle.Translate(comparedPos.x, comparedPos.y);

	if (playerRectangle.CompletelyOutside(comparedRectangle) == false)
	{		
		other.ResetToNewPosition();
		return true;
	}

	return false;

}

void EntityPlayer::ResetToNewPosition() //Was to be used if enemies were added
{
	Vector2 pos(GetPosition());

	pos.y = -1000;
	pos.x = -1000;

	m_alive = false;

	SetPosition(pos);
	SetPosition(pos);

}