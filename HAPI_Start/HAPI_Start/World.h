#pragma once

#include<vector>

class Visualisation;
class Entity;

class World
{
private:

	Visualisation * m_viz{ nullptr };

	std::vector<Entity*> m_entityVector;

	bool LoadLevel();
	void Update();


public:
	int score = 0;
	World();
	~World();

	void Run();
};
