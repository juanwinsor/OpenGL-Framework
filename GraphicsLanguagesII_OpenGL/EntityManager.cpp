#include "common.h"
#include <vector>
#include <string>
#include "Entity.h"
#include "EntityManager.h"

using namespace std;


EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	for(int i = 0; i < m_Entities.size(); i++)
	{
		delete m_Entities[i];
	}

	m_Entities.clear();
}


Entity* EntityManager::CreateEntity()
{
	Entity* entity = new Entity();
	m_Entities.push_back(entity);

	return entity;
}

void EntityManager::DeleteEntity(string name)
{
	int indexFound = -1;

	//look for the entity to delete
	for(int i = 0; i < m_Entities.size(); i++)
	{
		if(m_Entities[i]->Name() == name)
		{
			indexFound = i;
			break;
		}
	}

	//delete the entity if one was found
	if(indexFound > -1)
	{
		//delete m_Entities[indexFound];
		//m_Entities.erase(m_Entities.begin() + indexFound);
		m_EntitiesToDelete.push_back(indexFound);
	}

}

void EntityManager::DeleteEntity(Entity* entity)
{
	int indexFound = -1;

	for(int i = 0; i < m_Entities.size(); i++)
	{
		if(m_Entities[i] == entity)
		{
			indexFound = i;
			break;
		}
	}

	//delete the entity if one was found
	if(indexFound > -1)
	{
		m_EntitiesToDelete.push_back(indexFound);
	}
}

Entity* EntityManager::GetEntity(string name)
{
	for(int i = 0; i < m_Entities.size(); i++)
	{
		if(m_Entities[i]->Name() == name)
		{
			return m_Entities[i];
		}
	}

	return NULL;
}

std::vector<Entity*> EntityManager::GetEntities()
{
	return m_Entities;
}

void EntityManager::Update(GameTime gameTime)
{
	//clear any entities marked for deletion
	for(int i = 0; i < m_EntitiesToDelete.size(); i++)
	{
		delete m_Entities[m_EntitiesToDelete[i]];
		m_Entities.erase(m_Entities.begin() + m_EntitiesToDelete[i]);
	}

	m_EntitiesToDelete.clear();


	for(int i = 0; i < m_Entities.size(); i++)
	{
		m_Entities[i]->Update(gameTime);
	}
}

void EntityManager::Draw()
{
	for(int i = 0; i < m_Entities.size(); i++)
	{
		m_Entities[i]->Draw();
	}
}
