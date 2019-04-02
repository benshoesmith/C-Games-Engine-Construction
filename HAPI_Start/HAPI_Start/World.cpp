#include "World.h"
#include "Visualisation.h"
#include "EntityEnemy.h"
#include "EntityBackground.h"
#include "EntityPlayer.h"
#include <vector>
#include<stdlib.h>
#include<time.h>
#include <cassert>
#include <HAPI_lib.h>
#include <string.h>
using namespace HAPISPACE;

World::World()
{
}

World::~World()
{
	delete m_viz;

	for (auto p : m_entityVector)
		delete p;
}

bool World::LoadLevel()
{
	
	//Load Sprites
	if (!m_viz->CreateSprite("back", "Data\\background.png"))
		return false;

	if (!m_viz->CreateSprite("player", "Data\\playerFox.png", 4))
		return false;

	if (!m_viz->CreateSprite("chickens", "Data\\chickens.png", 4))
		return false;

	//Creating all Entities in order
	EntityBackground * newBackground = new EntityBackground("back");
	m_entityVector.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, -100));
	//creates player, no. sprites
	EntityPlayer *newPlayer = new EntityPlayer("player", 4);
	m_entityVector.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(300, 600));

	size_t chickenCount = 5;
	std::vector<EntityEnemy*> chickensArray(chickenCount);
	srand(time(NULL));
	//randomly spawning chickens
	for (int i = 0; i<chickenCount; ++i) 
	{
		int ramdomPositionX = 10 + rand() % (690 - 10);
		int ramdomPositionY = (100 + rand() % (600 - 100)) * -1; 
		chickensArray[i] = new EntityEnemy("chickens", 4);
		m_entityVector.push_back(chickensArray[i]);
		chickensArray[i]->SetPosition(Vector2((float)ramdomPositionX, (float)ramdomPositionY));
	}
}

constexpr DWORD kTickTime = 50;

void World::Update()
{
	//chicken sound options
	HAPI_TSoundOptions chickOptions(0.8f, false, 1.0f);
	HAPI.LoadSound("Data\\chicken.wav");
	DWORD lastTimeTicked = 0;
	DWORD lastTimeFired = 0;

	while (HAPI.Update())
	{
		HAPI.RenderText(10, 10, HAPI_TColour(255, 255, 255), "Score: " + std::to_string(score), 32);

		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };

		if (timeSinceLastTick >= kTickTime)
		{
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Update();
			}

			lastTimeTicked = HAPI.GetTime();

			//player-chicken collisions - if player collides with chicken, score+=1, play chicken sound
			for (size_t i = 0; i < m_entityVector.size(); i++)
			{				
				if (m_entityVector[i]->GetName() == "player")
				{
					for (size_t j = 0; j < m_entityVector.size(); j++)
					{

						if (m_entityVector[j]->GetSide() == ESide::eEnemy)
						{
							if (m_entityVector[i]->CheckCollision(*m_viz, *m_entityVector[j]))
							{
								HAPI.PlaySound("Data\\chicken.wav", chickOptions);
								score++;
							}
						}

					}
				}

			}
	
			timeSinceLastTick = 0;
		}

		float s = timeSinceLastTick / (float)kTickTime;
		assert(s >= 0 && s <= 1.0f);
	
		m_viz->ClearToGrayscale(0);
		for (auto p : m_entityVector)
		{
			p->Render(*m_viz, s);
		}
	}
}

void World::Run() {
	m_viz = new Visualisation;
	if (!m_viz->Initialise(600, 700))
		return;

	if (!LoadLevel())
		return;

	//Background Music
	HAPI_TSoundOptions bgOptions(0.8f, true, 1.0f);
	HAPI.LoadSound("Data\\background.mp3");
	HAPI.PlaySound("Data\\background.mp3", bgOptions);

	Update();

}