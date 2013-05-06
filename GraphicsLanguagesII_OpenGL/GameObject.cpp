#include "common.h"
#include "GameObject.h"



GameObject::GameObject()
{
	m_Active = false;

	m_Position = Vector3(0, 0, 0);
	m_Rotation = Vector3(0, 0, 0);
	m_Velocity = Vector3(0, 0, 0);
	
	m_Health = 0;

	m_TextureID = -1;
}

GameObject::~GameObject()
{

}

void GameObject::update(GameTime gameTime)
{

}

void GameObject::setPosition(Vector3 position)
{
	m_Position = position;
}

Vector3 GameObject::getPosition()
{
	return m_Position;
}