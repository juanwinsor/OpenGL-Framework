#include "common.h"
#include "Quad.h"

Quad::Quad(char* texturePath)
{
	m_TextureID = SOIL_load_OGL_texture(texturePath, 0, 0 /* 0 will specify to let SOIL generate a texture ID for us */, /*SOIL_FLAG_INVERT_Y | */SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//create a shader
	m_Shader = new Shader("Content/Shaders/vs.glsl", "Content/Shaders/fs.glsl");
	m_Shader->setTexture(m_TextureID);


	//make a quad
	VertexDefinition* vertices = new VertexDefinition[4];
	GLushort* indices = new GLushort[6];

	vertices[0].position[0] = -1;
	vertices[0].position[1] = -1;
	vertices[0].position[2] = 0;
	vertices[0].color[0] = 1;
	vertices[0].color[1] = 1;
	vertices[0].color[2] = 1;
	vertices[0].color[3] = 1;
	vertices[0].uv[0] = 0;
	vertices[0].uv[1] = 1;


	vertices[1].position[0] = 1;
	vertices[1].position[1] = -1;
	vertices[1].position[2] = 0;
	vertices[1].color[0] = 1;
	vertices[1].color[1] = 1;
	vertices[1].color[2] = 1;
	vertices[1].color[3] = 1;
	vertices[1].uv[0] = 1;
	vertices[1].uv[1] = 1;

	vertices[2].position[0] = -1;
	vertices[2].position[1] = 1;
	vertices[2].position[2] = 0;
	vertices[2].color[0] = 1;
	vertices[2].color[1] = 1;
	vertices[2].color[2] = 1;
	vertices[2].color[3] = 1;
	vertices[2].uv[0] = 0;
	vertices[2].uv[1] = 0;

	vertices[3].position[0] = 1;
	vertices[3].position[1] = 1;
	vertices[3].position[2] = 0;
	vertices[3].color[0] = 1;
	vertices[3].color[1] = 1;
	vertices[3].color[2] = 1;
	vertices[3].color[3] = 1;
	vertices[3].uv[0] = 1;
	vertices[3].uv[1] = 0;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 1;

	m_Quad = new RenderableElements();
	m_Quad->setVertexArray(vertices, indices, 6);
	m_Quad->setShader(m_Shader);
	m_Quad->setTextureID(m_TextureID);

	Renderer::getInstance()->addRenderable(m_Quad);

	Matrix world;
	world.SetIdentity();
	m_Rotation.x = 90;
	world.Rotate(m_Rotation.x, 1, 0, 0);
	world.Scale(300, 200, 1);
	world.SetPosition(0, -20, 0);
	m_Quad->setWorld(world);
}

Quad::Quad()
{
	
}

Quad::~Quad()
{
	Renderer::getInstance()->deleteRenderable(m_Quad);
	delete m_Quad;
	delete m_Shader;
}

void Quad::update(GameTime gameTime)
{
}