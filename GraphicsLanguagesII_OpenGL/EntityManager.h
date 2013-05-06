#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#include <vector>
#include <string>

class Entity;

using namespace std;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* CreateEntity();
	void DeleteEntity(string name);
	void DeleteEntity(Entity* entity);
	Entity* GetEntity(string name);
	std::vector<Entity*> GetEntities();

	void Update(GameTime gameTime);
	void Draw();
protected:
	std::vector<Entity*> m_Entities;
	std::vector<int> m_EntitiesToDelete;
};


#endif