#ifndef __UI_COMPONENT_TRANSFORM
#define __UI_COMPONENT_TRANSFORM

#include "common.h"
#include "Component.h"

class UI_Component_Transform : public Component
{
public:
	UI_Component_Transform()
	{
		m_Transform.SetIdentity();
	}

	~UI_Component_Transform()
	{

	}

	void Update(GameTime gameTime)
	{
		
	}

	void SetPosition(Vector3 position)
	{
		m_Transform.SetPosition(position);
	}

	void SetRotation(Vector3 rotation)
	{
		m_Transform.Rotate(rotation.z, 0, 0, 1);
		m_Transform.Rotate(rotation.y, 0, 1, 0);
		m_Transform.Rotate(rotation.x, 1, 0, 0);	
		
	}

	Matrix transform()
	{
		Matrix matrix;		

		Entity* parent = this->Owner->GetParent();

		if(parent != NULL)
		{			
			//copy the local matrix
			matrix = m_Transform;
			//multiply the child matrix by the parent matrix
			UI_Component_Transform* transform = (UI_Component_Transform*)this->Owner->GetParent()->getComponent(UI_COMPONENT_TRANSFORM);
			matrix.Multiply(&(transform->transform()));
		}
		else
		{
			//matrix.SetIdentity();
			matrix = m_Transform;
		}

		return matrix;
	}

protected:
	Matrix m_Transform;
};

#endif