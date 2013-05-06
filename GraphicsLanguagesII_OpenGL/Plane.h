#ifndef __PLANE_H
#define __PLANE_H


#include "GameObject.h"
#include "RenderableElements.h"
#include "Shader.h"

class Plane : public GameObject
{
public:
	Plane();
	~Plane();

protected:
	RenderableElements* m_Plane;
	Shader* m_Shader;
};


#endif