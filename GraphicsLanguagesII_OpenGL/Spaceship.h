#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include "RenderableElements.h"
#include "ThrusterShader.h"
#include "MouseShader.h"


class Spaceship
{
public:
	Spaceship();
	~Spaceship();

	void update(double delta);

protected:
	RenderableElements* m_ShipBody;
	RenderableElements* m_ShipCockpit;
	RenderableElements* m_ShipLeftWing;
	RenderableElements* m_ShipRightWing;
	RenderableElements* m_ShipThruster;

	Shader* m_ShipShader;
	ThrusterShader* m_ThrusterShader;
	MouseShader* m_MouseShader;

	double m_TotalTime;

	Matrix m_World;
};


#endif