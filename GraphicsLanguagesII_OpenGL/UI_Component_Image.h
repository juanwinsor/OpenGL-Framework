#ifndef __UI_COMPONENT_IMAGE
#define __UI_COMPONENT_IMAGE

#include "common.h"
#include "Renderer2D.h"
#include "Component.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "UI_Component_Transform.h"

class UI_Component_Image : public Component
{
public:

	UI_Component_Image()
	{
		m_Image = NULL;
	}

	~UI_Component_Image()
	{
		if(m_Image != NULL)
		{
			delete m_Image;
		}
	}

	void Draw()
	{
		//get this objects transform to get its translation
		UI_Component_Transform* transform = (UI_Component_Transform*)Owner->getComponent(UI_COMPONENT_TRANSFORM);
		//get the translation of the entity to use as the position of the texture
		float left = transform->transform().m41;
		float top = transform->transform().m42;
		Renderer2D::getInstance()->drawTexture(m_Image->textureID(), Vector4(left, top, 200, 100), Vector4(0, 0, 0, 0), Vector3(1, 1, 1), Vector2(0, 0), 45);
	}

	void loadImage(char* filename)
	{
		m_Image = new Texture2D(filename);
	}

protected:
	Texture2D* m_Image;
};

#endif