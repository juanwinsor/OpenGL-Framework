#ifndef __QUAD_H
#define __QUAD_H


#include "GameObject.h"
#include "RenderableElements.h"
#include "Shader.h"

class Quad : public GameObject
{
public:
	Quad();
	Quad(char* texturePath);
	~Quad();
	void update(GameTime gameTime);
protected:
	RenderableElements* m_Quad;
	Shader* m_Shader;
};

#endif

