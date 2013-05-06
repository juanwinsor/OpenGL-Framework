#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include <map>
#include <vector>
#include "EntityManager.h"

class Component;

using namespace std;

class Entity
{
public:
	Entity();
	~Entity();

	string Name();
	void setName(string name);

	//children
	Entity* createChild();

	//components
	Component* getComponent(ComponentType componentType);

	template <typename T> Component* addComponent(ComponentType componentType)
	{
		//create a new component of type T
		Component* component = new T();
		//call its attach
		component->Owner = this;
		component->Attach();		
		//insert the component into the component list
		m_Components.insert(pair<ComponentType, Component*>(componentType, component));

		return component;
	}

	void removeComponent(ComponentType componentType);

	virtual void Update(GameTime gameTime);
	virtual void Draw();


	virtual Matrix* transform();


	void SetManager(EntityManager* entityManager);
	EntityManager* GetManager();
	void SetParent(Entity* parent);
	Entity* GetParent();

protected:	
	EntityManager* m_Manager;
	Entity* m_Parent;

	string m_Name;
	float m_PositionX;
	float m_PositionY;
	float m_Width;
	float m_Height;
	map<ComponentType, Component*>  m_Components;
	Matrix* m_Transform;

	//vector<Entity*> m_Children;
};

#endif