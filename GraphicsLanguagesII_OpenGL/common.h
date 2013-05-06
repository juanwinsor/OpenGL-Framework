#ifndef __COMMON_H
#define __COMMON_H

#define PI 3.1415926535897932384626433832795f

#include <Windows.h>
#include <stdio.h>
#include <math.h>


struct VertexDefinition
{
	float position[3];
	float color[4];
	float uv[2];
	float normal[3];
};


struct GameTime
{
	double ElapsedTime;
	double TotalTime;
};


enum ComponentType
{
	//GAME COMPONENTS
	DUMMY_COMPONENT,	
	COMPONENT_PATHFINDING,
	COMPONENT_PATHFINDINGFOLLOW,	
	COMPONENT_PLAYERMOVEMENT,
	COMPONENT_COLLISIONRECTANGLE,
	COMPONENT_STATICTEXTURE,
	COMPONENT_PARTICLEEMITTER,
	COMPONENT_FIREBALL,	
	COMPONENT_MANA,
	COMPONENT_HEALTH,
	COMPONENT_MONSTERMELEE,

	//UI COMPONENTS
	UI_COMPONENT_TRANSFORM,
	UI_COMPONENT_IMAGE,
	UI_COMPONENT_BUTTON
};


#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/glfw.h"
#include "Utility/Vector.h"
#include "Utility/Matrix.h"
#include "Utility/soil/SOIL.h"


#endif