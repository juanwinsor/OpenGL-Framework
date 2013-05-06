#include "common.h"
#include "Spaceship.h"
#include "Renderer.h"
#include "RenderableElements.h"
#include "InputManager.h"

Spaceship::Spaceship()
{
	m_World.SetIdentity();
	m_TotalTime = 0;

	m_ShipShader = new Shader("Content/Shaders/vs.glsl", "Content/Shaders/fs.glsl");	
	m_ThrusterShader = new ThrusterShader("Content/Shaders/vsThruster.glsl", "Content/Shaders/fs.glsl");	
	m_MouseShader = new MouseShader("Content/Shaders/vsMouse.glsl", "Content/Shaders/fs.glsl");

	//create ship body
	VertexDefinition* verticesBody = new VertexDefinition[5];
	GLushort* indicesBody = new GLushort[15];

	//ship body
	verticesBody[0].position[0] = 0; //p1
	verticesBody[0].position[1] = 0.5f;
	verticesBody[0].position[2] = -12;
	verticesBody[0].color[0] = 0.7f;
	verticesBody[0].color[1] = 0.7f;
	verticesBody[0].color[2] = 0.7f;
	verticesBody[0].color[3] = 1;

	verticesBody[1].position[0] = -2; //p2
	verticesBody[1].position[1] = 0;
	verticesBody[1].position[2] = 0;
	verticesBody[1].color[0] = 0.7f;
	verticesBody[1].color[1] = 0.7f;
	verticesBody[1].color[2] = 0.7f;
	verticesBody[1].color[3] = 1;

	verticesBody[2].position[0] = 0; //p3
	verticesBody[2].position[1] = 1;
	verticesBody[2].position[2] = -3;
	verticesBody[2].color[0] = 0.7f;
	verticesBody[2].color[1] = 0.7f;
	verticesBody[2].color[2] = 0.7f;
	verticesBody[2].color[3] = 1;

	verticesBody[3].position[0] = 2; //p4
	verticesBody[3].position[1] = 0;
	verticesBody[3].position[2] = 0;
	verticesBody[3].color[0] = 0.7f;
	verticesBody[3].color[1] = 0.7f;
	verticesBody[3].color[2] = 0.7f;
	verticesBody[3].color[3] = 1;

	verticesBody[4].position[0] = 0; //p5
	verticesBody[4].position[1] = -1;
	verticesBody[4].position[2] = -1;
	verticesBody[4].color[0] = 0.7f;
	verticesBody[4].color[1] = 0.7f;
	verticesBody[4].color[2] = 0.7f;
	verticesBody[4].color[3] = 1;

	indicesBody[0] = 0;
	indicesBody[1] = 1;
	indicesBody[2] = 2;
	indicesBody[3] = 2;
	indicesBody[4] = 3;
	indicesBody[5] = 0;
	indicesBody[6] = 4;
	indicesBody[7] = 1;
	indicesBody[8] = 0;
	indicesBody[9] = 4;
	indicesBody[10] = 0;
	indicesBody[11] = 3;
	indicesBody[12] = 1;
	indicesBody[13] = 4;
	indicesBody[14] = 3;

	m_ShipBody = new RenderableElements();
	m_ShipBody->setShader(m_ShipShader);
	m_ShipBody->setVertexArray(verticesBody, indicesBody, 15);
	Renderer::getInstance()->addRenderable(m_ShipBody);

	//left wing
	VertexDefinition* verticesLeftWing = new VertexDefinition[4];
	GLushort* indicesLeftWing = new GLushort[12];

	verticesLeftWing[0].position[0] = -2; //0
	verticesLeftWing[0].position[1] = 0;
	verticesLeftWing[0].position[2] = 0;
	verticesLeftWing[0].color[0] = 0.7f;
	verticesLeftWing[0].color[1] = 0.7f;
	verticesLeftWing[0].color[2] = 0.7f;
	verticesLeftWing[0].color[3] = 1;

	verticesLeftWing[1].position[0] = -4; //1
	verticesLeftWing[1].position[1] = 0;
	verticesLeftWing[1].position[2] = 0;
	verticesLeftWing[1].color[0] = 0.7f;
	verticesLeftWing[1].color[1] = 0.7f;
	verticesLeftWing[1].color[2] = 0.7f;
	verticesLeftWing[1].color[3] = 1;

	verticesLeftWing[2].position[0] = -6; //2
	verticesLeftWing[2].position[1] = -2;
	verticesLeftWing[2].position[2] = 7;
	verticesLeftWing[2].color[0] = 0.7f;
	verticesLeftWing[2].color[1] = 0.7f;
	verticesLeftWing[2].color[2] = 0.7f;
	verticesLeftWing[2].color[3] = 1;

	verticesLeftWing[3].position[0] = -3.5f; //3
	verticesLeftWing[3].position[1] = -1;
	verticesLeftWing[3].position[2] = 0.5f;
	verticesLeftWing[3].color[0] = 0.7f;
	verticesLeftWing[3].color[1] = 0.7f;
	verticesLeftWing[3].color[2] = 0.7f;
	verticesLeftWing[3].color[3] = 1;

	indicesLeftWing[0] = 0;
	indicesLeftWing[1] = 1;
	indicesLeftWing[2] = 2;
	indicesLeftWing[3] = 2;
	indicesLeftWing[4] = 3;
	indicesLeftWing[5] = 0;
	indicesLeftWing[6] = 2;
	indicesLeftWing[7] = 1;
	indicesLeftWing[8] = 3;
	indicesLeftWing[9] = 0;
	indicesLeftWing[10] = 3;
	indicesLeftWing[11] = 1;

	m_ShipLeftWing = new RenderableElements();
	m_ShipLeftWing->setShader(m_ShipShader);
	m_ShipLeftWing->setVertexArray(verticesLeftWing, indicesLeftWing, 12);
	Renderer::getInstance()->addRenderable(m_ShipLeftWing);


	//right wing
	VertexDefinition* verticesRightWing = new VertexDefinition[4];
	GLushort* indicesRightWing = new GLushort[12];

	verticesRightWing[0].position[0] = 2; //0
	verticesRightWing[0].position[1] = 0;
	verticesRightWing[0].position[2] = 0;
	verticesRightWing[0].color[0] = 0.7f;
	verticesRightWing[0].color[1] = 0.7f;
	verticesRightWing[0].color[2] = 0.7f;
	verticesRightWing[0].color[3] = 1;

	verticesRightWing[1].position[0] = 4; //1
	verticesRightWing[1].position[1] = 0;
	verticesRightWing[1].position[2] = 0;
	verticesRightWing[1].color[0] = 0.7f;
	verticesRightWing[1].color[1] = 0.7f;
	verticesRightWing[1].color[2] = 0.7f;
	verticesRightWing[1].color[3] = 1;

	verticesRightWing[2].position[0] = 6; //2
	verticesRightWing[2].position[1] = -2;
	verticesRightWing[2].position[2] = 7;
	verticesRightWing[2].color[0] = 0.7f;
	verticesRightWing[2].color[1] = 0.7f;
	verticesRightWing[2].color[2] = 0.7f;
	verticesRightWing[2].color[3] = 1;

	verticesRightWing[3].position[0] = 3.5f; //3
	verticesRightWing[3].position[1] = -1;
	verticesRightWing[3].position[2] = 0.5f;
	verticesRightWing[3].color[0] = 0.7f;
	verticesRightWing[3].color[1] = 0.7f;
	verticesRightWing[3].color[2] = 0.7f;
	verticesRightWing[3].color[3] = 1;

	indicesRightWing[0] = 0;
	indicesRightWing[1] = 2;
	indicesRightWing[2] = 1;
	indicesRightWing[3] = 0;
	indicesRightWing[4] = 3;
	indicesRightWing[5] = 2;
	indicesRightWing[6] = 3;
	indicesRightWing[7] = 1;
	indicesRightWing[8] = 2;
	indicesRightWing[9] = 0;
	indicesRightWing[10] = 1;
	indicesRightWing[11] = 3;

	m_ShipRightWing = new RenderableElements();
	m_ShipRightWing->setShader(m_ShipShader);
	m_ShipRightWing->setVertexArray(verticesRightWing, indicesRightWing, 12);
	Renderer::getInstance()->addRenderable(m_ShipRightWing);

	//thruster
	VertexDefinition* verticesThruster = new VertexDefinition[3];
	GLushort* indicesThruster = new GLushort[3];

	verticesThruster[0].position[0] = -2; //0
	verticesThruster[0].position[1] = 0;
	verticesThruster[0].position[2] = 0;
	verticesThruster[0].color[0] = 1.0f;
	verticesThruster[0].color[1] = 0.0f;
	verticesThruster[0].color[2] = 0.0f;
	verticesThruster[0].color[3] = 1;

	verticesThruster[1].position[0] = 0; //1
	verticesThruster[1].position[1] = 1;
	verticesThruster[1].position[2] = 2;
	verticesThruster[1].color[0] = 1.0f;
	verticesThruster[1].color[1] = 0.0f;
	verticesThruster[1].color[2] = 0.0f;
	verticesThruster[1].color[3] = 1;

	verticesThruster[2].position[0] = 2; //2
	verticesThruster[2].position[1] = 0;
	verticesThruster[2].position[2] = 0;
	verticesThruster[2].color[0] = 1.0f;
	verticesThruster[2].color[1] = 0.0f;
	verticesThruster[2].color[2] = 0.0f;
	verticesThruster[2].color[3] = 1;

	indicesThruster[0] = 0;
	indicesThruster[1] = 1;
	indicesThruster[2] = 2;

	m_ShipThruster = new RenderableElements();
	m_ShipThruster->setShader(m_ThrusterShader);
	m_ShipThruster->setVertexArray(verticesThruster, indicesThruster, 3);
	Renderer::getInstance()->addRenderable(m_ShipThruster);

	//cockpit of ship
	VertexDefinition* verticesCockpit = new VertexDefinition[5];
	GLushort* indicesCockpit = new GLushort[12];

	verticesCockpit[0].position[0] = 0; //0
	verticesCockpit[0].position[1] = 1;
	verticesCockpit[0].position[2] = -3;
	verticesCockpit[0].color[0] = 0.9f;
	verticesCockpit[0].color[1] = 0.9f;
	verticesCockpit[0].color[2] = 0.9f;
	verticesCockpit[0].color[3] = 1;

	verticesCockpit[1].position[0] = -2; //1
	verticesCockpit[1].position[1] = 0;
	verticesCockpit[1].position[2] = 0;
	verticesCockpit[1].color[0] = 0.9f;
	verticesCockpit[1].color[1] = 0.9f;
	verticesCockpit[1].color[2] = 0.9f;
	verticesCockpit[1].color[3] = 1;

	verticesCockpit[2].position[0] = 0; //2
	verticesCockpit[2].position[1] = 2;
	verticesCockpit[2].position[2] = 0;
	verticesCockpit[2].color[0] = 0.9f;
	verticesCockpit[2].color[1] = 0.9f;
	verticesCockpit[2].color[2] = 0.9f;
	verticesCockpit[2].color[3] = 1;

	verticesCockpit[3].position[0] = 2; //3
	verticesCockpit[3].position[1] = 0;
	verticesCockpit[3].position[2] = 0;
	verticesCockpit[3].color[0] = 0.9f;
	verticesCockpit[3].color[1] = 0.9f;
	verticesCockpit[3].color[2] = 0.9f;
	verticesCockpit[3].color[3] = 1;

	verticesCockpit[4].position[0] = 0; //4
	verticesCockpit[4].position[1] = 1;
	verticesCockpit[4].position[2] = 2;
	verticesCockpit[4].color[0] = 0.9f;
	verticesCockpit[4].color[1] = 0.9f;
	verticesCockpit[4].color[2] = 0.9f;
	verticesCockpit[4].color[3] = 1;

	indicesCockpit[0] = 0;
	indicesCockpit[1] = 1;
	indicesCockpit[2] = 2;
	indicesCockpit[3] = 1;
	indicesCockpit[4] = 4;
	indicesCockpit[5] = 2;
	indicesCockpit[6] = 0;
	indicesCockpit[7] = 2;
	indicesCockpit[8] = 3;
	indicesCockpit[9] = 2;
	indicesCockpit[10] = 4;
	indicesCockpit[11] = 3;

	m_ShipCockpit = new RenderableElements();
	m_ShipCockpit->setShader(m_MouseShader);
	m_ShipCockpit->setVertexArray(verticesCockpit, indicesCockpit, 12);
	Renderer::getInstance()->addRenderable(m_ShipCockpit);
	
}

Spaceship::~Spaceship()
{
	//cleanup renderables
	Renderer::getInstance()->deleteRenderable(m_ShipBody);
	Renderer::getInstance()->deleteRenderable(m_ShipCockpit);
	Renderer::getInstance()->deleteRenderable(m_ShipLeftWing);
	Renderer::getInstance()->deleteRenderable(m_ShipRightWing);
	Renderer::getInstance()->deleteRenderable(m_ShipThruster);

	delete m_ShipBody;
	delete m_ShipCockpit;
	delete m_ShipLeftWing;
	delete m_ShipRightWing;
	delete m_ShipThruster;
	delete m_ShipShader;
	delete m_ThrusterShader;
	delete m_MouseShader;
}

void Spaceship::update(double delta)
{
	m_TotalTime = delta;

	//rotate the ship to point in general direction of mouse if the RMB is down
	if(InputManager::getInstance()->mouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		m_World.SetIdentity();
		Vector3 target(InputManager::getInstance()->mousePosition().x - (Renderer::getInstance()->screenWidth() / 2), -InputManager::getInstance()->mousePosition().y + (Renderer::getInstance()->screenHeight() / 2), 100);
		Vector3 eye(0, 0, 0);
		Vector3 up(0, 1, 0);
		m_World.SetLookAtLH(eye, up, target);
	}

	//change cockpit color by mouse
	if(InputManager::getInstance()->mouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		m_MouseShader->setMousePosition(InputManager::getInstance()->mousePosition().x, InputManager::getInstance()->mousePosition().y);
	}

	m_ShipBody->setWorld(m_World);
	m_ShipCockpit->setWorld(m_World);
	m_ShipLeftWing->setWorld(m_World);
	m_ShipRightWing->setWorld(m_World);
	m_ShipThruster->setWorld(m_World);

	m_ThrusterShader->setTime(m_TotalTime);
}
