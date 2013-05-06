#include "common.h"
#include "RenderableElements.h"


RenderableElements::RenderableElements()
{
	m_Vertices = NULL;
	m_Indices = NULL;

	m_Color = Vector4(1, 1, 1, 1);

	//initialize world matrix
	m_World.SetIdentity();
}

RenderableElements::~RenderableElements()
{
	//delete the vertices if they've been set
	if(m_Vertices != NULL)
	{
		delete[] m_Vertices;
		delete[] m_Indices;
	}
}

void RenderableElements::draw()
{
	//apply the shader
	m_Shader->apply();


	// Set up the uniforms.
	glUniformMatrix4fv(m_Shader->worldViewProjectionHandle(), 1, false, (GLfloat*)&Renderer::getInstance()->camera()->worldViewProjection(m_World));

	//vertex position
	glVertexAttribPointer(m_Shader->vsPositionHandle(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->position); //&Verts->position);
    glEnableVertexAttribArray(m_Shader->vsPositionHandle());
	//vertex color
	glVertexAttribPointer(m_Shader->vsColorHandle(), 4, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->color); //m_Vertices->color); //&Verts->color);
    glEnableVertexAttribArray(m_Shader->vsColorHandle());
	//uv coords
	glVertexAttribPointer(m_Shader->vsUVCoordinateHandle(), 2, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->uv);
    glEnableVertexAttribArray(m_Shader->vsUVCoordinateHandle());

	//set uniforms
	m_Shader->setUniform("u_Color", Vector3(m_Color.x, m_Color.y, m_Color.z));

	//draw the elements
	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_SHORT, m_Indices);

	glDisableVertexAttribArray(m_Shader->vsPositionHandle());
    glDisableVertexAttribArray(m_Shader->vsColorHandle());
	glDisableVertexAttribArray(m_Shader->vsUVCoordinateHandle());
}

void RenderableElements::setVertexArray(VertexDefinition* vertices, GLushort* indices, unsigned int numberOfIndices)
//void RenderableElements::setVertexArray(VertexDefinition vertices[], GLushort indices[])
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_NumberOfIndices = numberOfIndices;
}

void RenderableElements::setShader(Shader* shader)
{
	m_Shader = shader;
}

void RenderableElements::setWorld(Matrix world)
{
	m_World = world;
}

Matrix RenderableElements::world()
{
	return m_World;
}

void RenderableElements::setTextureID(GLint textureID)
{
	m_TextureID = textureID;
}

void RenderableElements::setColor(Vector4 color)
{
	m_Color = color;
}