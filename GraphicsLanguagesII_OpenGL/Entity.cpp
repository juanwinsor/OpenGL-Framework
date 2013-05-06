#include "common.h"
#include <string>
#include "Entity.h"
#include "Component.h"
//#include "Constants.h"

//#include "TestComponent.h"

using namespace std;

Entity::Entity()
{
	m_Transform = new Matrix();
	m_Parent = NULL;
}

Entity::~Entity()
{
	delete m_Transform;

	map<ComponentType, Component*>::iterator it;

	for(it = m_Components.begin(); it != m_Components.end(); it++)
	{
		m_Components.at(it->first)->Detach();
		//delete the component
		delete m_Components.at(it->first);
		//break;
	}

	m_Components.clear();

}

string Entity::Name()
{
	return m_Name;
}

void Entity::setName(string name)
{
	m_Name = name;
}

Component* Entity::getComponent(ComponentType componentType)
{
	//std::string testString = this->Name();
	map<ComponentType, Component*>::iterator it = m_Components.find(componentType);

	

	if(it != m_Components.end())
	{
		return it->second;
	}
}

void Entity::removeComponent(ComponentType componentType)
{
	map<ComponentType, Component*>::iterator it;
	for(it = m_Components.begin(); it != m_Components.end(); it++)
	{
		if(it->first == componentType)
		{
			break;
		}
	}

	if(it->first != NULL)
	{
		it->second->Detach();
		m_Components.erase(it);
	}
}

void Entity::Update(GameTime gameTime)
{
	map<ComponentType, Component*>::iterator it;

	for(it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Update(gameTime);
	}
}

void Entity::Draw()
{
	map<ComponentType, Component*>::iterator it;

	for(it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Draw();
	}
}

Matrix* Entity::transform()
{
	return m_Transform;
}

Entity* Entity::createChild()
{
	//create the entity with the entity manager
	Entity* entity = m_Manager->CreateEntity();
	//pass a reference to the entitymanager
	entity->SetManager(m_Manager);
	//set the parent of this child to this instance
	entity->SetParent(this);

	return entity;
}

void Entity::SetManager(EntityManager* entityManager)
{
	m_Manager = entityManager;
}

void Entity::SetParent(Entity* parent)
{
	m_Parent = parent;
}

Entity* Entity::GetParent()
{
	return m_Parent;
}

EntityManager* Entity::GetManager()
{
	return m_Manager;
}