#ifndef __PLAYER_H
#define __PLAYER_H


#include "Shader.h"
#include "RenderableElements.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(int playerID);
	~Player();

	void update(GameTime gameTime);

protected:
	RenderableElements* m_ShipBody;
	RenderableElements* m_ShipCockpit;
	RenderableElements* m_ShipLeftWing;
	RenderableElements* m_ShipRightWing;
	RenderableElements* m_ShipThruster;

	Shader* m_ShipShader;

	double m_TotalTime;

	Matrix m_World;

	int m_PlayerID;
};

#endif