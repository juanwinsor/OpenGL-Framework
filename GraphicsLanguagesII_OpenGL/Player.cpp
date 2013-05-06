#include "common.h"
#include "Player.h"



Player::Player(int playerID)
{
	m_PlayerID = playerID;

	GameObject::GameObject();


	m_TextureID = SOIL_load_OGL_texture("Content/Textures/firefly.png", 0, 0 /* 0 will specify to let SOIL generate a texture ID for us */, /*SOIL_FLAG_INVERT_Y | */SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	m_World.SetIdentity();
	m_TotalTime = 0;

	m_ShipShader = new Shader("Content/Shaders/vs.glsl", "Content/Shaders/fs.glsl");	
	m_ShipShader->setTexture(m_TextureID);
	glUniform4f(m_ShipShader->vsColorHandle(), 1, 1, 1, 1);


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
	verticesBody[0].uv[0] = 0;
	verticesBody[0].uv[1] = 0;

	verticesBody[1].position[0] = -2; //p2
	verticesBody[1].position[1] = 0;
	verticesBody[1].position[2] = 0;
	verticesBody[1].color[0] = 0.7f;
	verticesBody[1].color[1] = 0.7f;
	verticesBody[1].color[2] = 0.7f;
	verticesBody[1].color[3] = 1;
	verticesBody[1].uv[0] = 0;
	verticesBody[1].uv[1] = 0;

	verticesBody[2].position[0] = 0; //p3
	verticesBody[2].position[1] = 1;
	verticesBody[2].position[2] = -3;
	verticesBody[2].color[0] = 0.7f;
	verticesBody[2].color[1] = 0.7f;
	verticesBody[2].color[2] = 0.7f;
	verticesBody[2].color[3] = 1;
	verticesBody[2].uv[0] = 0;
	verticesBody[2].uv[1] = 0;

	verticesBody[3].position[0] = 2; //p4
	verticesBody[3].position[1] = 0;
	verticesBody[3].position[2] = 0;
	verticesBody[3].color[0] = 0.7f;
	verticesBody[3].color[1] = 0.7f;
	verticesBody[3].color[2] = 0.7f;
	verticesBody[3].color[3] = 1;
	verticesBody[3].uv[0] = 0;
	verticesBody[3].uv[1] = 0;

	verticesBody[4].position[0] = 0; //p5
	verticesBody[4].position[1] = -1;
	verticesBody[4].position[2] = -1;
	verticesBody[4].color[0] = 0.7f;
	verticesBody[4].color[1] = 0.7f;
	verticesBody[4].color[2] = 0.7f;
	verticesBody[4].color[3] = 1;
	verticesBody[4].uv[0] = 0;
	verticesBody[4].uv[1] = 0;

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
	verticesLeftWing[0].uv[0] = 0;
	verticesLeftWing[0].uv[1] = 0;

	verticesLeftWing[1].position[0] = -4; //1
	verticesLeftWing[1].position[1] = 0;
	verticesLeftWing[1].position[2] = 0;
	verticesLeftWing[1].color[0] = 0.7f;
	verticesLeftWing[1].color[1] = 0.7f;
	verticesLeftWing[1].color[2] = 0.7f;
	verticesLeftWing[1].color[3] = 1;
	verticesLeftWing[1].uv[0] = 0;
	verticesLeftWing[1].uv[1] = 0;

	verticesLeftWing[2].position[0] = -6; //2
	verticesLeftWing[2].position[1] = -2;
	verticesLeftWing[2].position[2] = 7;
	verticesLeftWing[2].color[0] = 0.7f;
	verticesLeftWing[2].color[1] = 0.7f;
	verticesLeftWing[2].color[2] = 0.7f;
	verticesLeftWing[2].color[3] = 1;
	verticesLeftWing[2].uv[0] = 0;
	verticesLeftWing[2].uv[1] = 0;

	verticesLeftWing[3].position[0] = -3.5f; //3
	verticesLeftWing[3].position[1] = -1;
	verticesLeftWing[3].position[2] = 0.5f;
	verticesLeftWing[3].color[0] = 0.7f;
	verticesLeftWing[3].color[1] = 0.7f;
	verticesLeftWing[3].color[2] = 0.7f;
	verticesLeftWing[3].color[3] = 1;
	verticesLeftWing[3].uv[0] = 0;
	verticesLeftWing[3].uv[1] = 0;

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
	verticesRightWing[0].uv[0] = 0;
	verticesRightWing[0].uv[1] = 0;

	verticesRightWing[1].position[0] = 4; //1
	verticesRightWing[1].position[1] = 0;
	verticesRightWing[1].position[2] = 0;
	verticesRightWing[1].color[0] = 0.7f;
	verticesRightWing[1].color[1] = 0.7f;
	verticesRightWing[1].color[2] = 0.7f;
	verticesRightWing[1].color[3] = 1;
	verticesRightWing[1].uv[0] = 0;
	verticesRightWing[1].uv[1] = 0;

	verticesRightWing[2].position[0] = 6; //2
	verticesRightWing[2].position[1] = -2;
	verticesRightWing[2].position[2] = 7;
	verticesRightWing[2].color[0] = 0.7f;
	verticesRightWing[2].color[1] = 0.7f;
	verticesRightWing[2].color[2] = 0.7f;
	verticesRightWing[2].color[3] = 1;
	verticesRightWing[2].uv[0] = 0;
	verticesRightWing[2].uv[1] = 0;

	verticesRightWing[3].position[0] = 3.5f; //3
	verticesRightWing[3].position[1] = -1;
	verticesRightWing[3].position[2] = 0.5f;
	verticesRightWing[3].color[0] = 0.7f;
	verticesRightWing[3].color[1] = 0.7f;
	verticesRightWing[3].color[2] = 0.7f;
	verticesRightWing[3].color[3] = 1;
	verticesRightWing[3].uv[0] = 0;
	verticesRightWing[3].uv[1] = 0;

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
	verticesThruster[0].uv[0] = 0;
	verticesThruster[0].uv[1] = 0;

	verticesThruster[1].position[0] = 0; //1
	verticesThruster[1].position[1] = 1;
	verticesThruster[1].position[2] = 2;
	verticesThruster[1].color[0] = 1.0f;
	verticesThruster[1].color[1] = 0.0f;
	verticesThruster[1].color[2] = 0.0f;
	verticesThruster[1].color[3] = 1;
	verticesThruster[1].uv[0] = 0;
	verticesThruster[1].uv[1] = 0;

	verticesThruster[2].position[0] = 2; //2
	verticesThruster[2].position[1] = 0;
	verticesThruster[2].position[2] = 0;
	verticesThruster[2].color[0] = 1.0f;
	verticesThruster[2].color[1] = 0.0f;
	verticesThruster[2].color[2] = 0.0f;
	verticesThruster[2].color[3] = 1;
	verticesThruster[2].uv[0] = 0;
	verticesThruster[2].uv[1] = 0;

	indicesThruster[0] = 0;
	indicesThruster[1] = 1;
	indicesThruster[2] = 2;

	m_ShipThruster = new RenderableElements();
	m_ShipThruster->setShader(m_ShipShader);
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
	verticesCockpit[0].uv[0] = 0;
	verticesCockpit[0].uv[1] = 0;

	verticesCockpit[1].position[0] = -2; //1
	verticesCockpit[1].position[1] = 0;
	verticesCockpit[1].position[2] = 0;
	verticesCockpit[1].color[0] = 0.9f;
	verticesCockpit[1].color[1] = 0.9f;
	verticesCockpit[1].color[2] = 0.9f;
	verticesCockpit[1].color[3] = 1;
	verticesCockpit[1].uv[0] = 0;
	verticesCockpit[1].uv[1] = 0;

	verticesCockpit[2].position[0] = 0; //2
	verticesCockpit[2].position[1] = 2;
	verticesCockpit[2].position[2] = 0;
	verticesCockpit[2].color[0] = 0.9f;
	verticesCockpit[2].color[1] = 0.9f;
	verticesCockpit[2].color[2] = 0.9f;
	verticesCockpit[2].color[3] = 1;
	verticesCockpit[2].uv[0] = 0;
	verticesCockpit[2].uv[1] = 0;

	verticesCockpit[3].position[0] = 2; //3
	verticesCockpit[3].position[1] = 0;
	verticesCockpit[3].position[2] = 0;
	verticesCockpit[3].color[0] = 0.9f;
	verticesCockpit[3].color[1] = 0.9f;
	verticesCockpit[3].color[2] = 0.9f;
	verticesCockpit[3].color[3] = 1;
	verticesCockpit[3].uv[0] = 0;
	verticesCockpit[3].uv[1] = 0;

	verticesCockpit[4].position[0] = 0; //4
	verticesCockpit[4].position[1] = 1;
	verticesCockpit[4].position[2] = 2;
	verticesCockpit[4].color[0] = 0.9f;
	verticesCockpit[4].color[1] = 0.9f;
	verticesCockpit[4].color[2] = 0.9f;
	verticesCockpit[4].color[3] = 1;
	verticesCockpit[4].uv[0] = 0;
	verticesCockpit[4].uv[1] = 0;

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
	m_ShipCockpit->setShader(m_ShipShader);
	m_ShipCockpit->setVertexArray(verticesCockpit, indicesCockpit, 12);
	Renderer::getInstance()->addRenderable(m_ShipCockpit);
}


Player::~Player()
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

}


void Player::update(GameTime gameTime)
{
	char forward;
	char left;
	char right;

	if(m_PlayerID == 1)
	{
		forward = 'W';
		left = 'A';
		right = 'D';
	}
	else
	{
		forward = 'I';
		left = 'J';
		right = 'L';
	}

	if(glfwGetKey(forward))
	{
		m_Velocity.Set(sin(m_Rotation.y / 180 * PI), 0, -cos(m_Rotation.y / 180 * PI));
		m_Velocity = m_Velocity * gameTime.ElapsedTime * 40.0f;
	}
	if(glfwGetKey(left))
	{
		m_Rotation.y += gameTime.ElapsedTime * -300;
	}
	if(glfwGetKey(right))
	{
		m_Rotation.y += gameTime.ElapsedTime * 300;
	}

	m_World.SetIdentity();
	m_Position = m_Position + m_Velocity;
	m_Velocity = m_Velocity * 0.95f;
	m_World.Rotate(m_Rotation.y, 0, 1, 0);	
	m_World.SetPosition(m_Position);
	

	m_ShipBody->setWorld(m_World);
	m_ShipCockpit->setWorld(m_World);
	m_ShipLeftWing->setWorld(m_World);
	m_ShipRightWing->setWorld(m_World);
	m_ShipThruster->setWorld(m_World);

	//m_ShipShader->setUniform("u_Color", Vector3(0, 1, 0));
	/*m_ShipBody->setColor(Vector4(0, 1, 0, 1));
	m_ShipCockpit->setColor(Vector4(0, 1, 0, 1));
	m_ShipLeftWing->setColor(Vector4(0, 1, 0, 1));
	m_ShipRightWing->setColor(Vector4(0, 1, 0, 1));
	m_ShipThruster->setColor(Vector4(0, 1, 0, 1));*/

}
//GLM matrix library
//http://sourceforge.net/projects/ogl-math/
