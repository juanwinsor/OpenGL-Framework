#ifndef __RENDERABLEELEMENTS_H
#define __RENDERABLEELEMENTS_H


#include "Shader.h"
#include "Renderable.h"
#include "Renderer.h"

class RenderableElements : public Renderable
{
public:


	RenderableElements();
	~RenderableElements();

	void draw();
	void setVertexArray(VertexDefinition* vertices, GLushort* indices, unsigned int numberOfIndices);
	void setShader(Shader* shader);

	void setWorld(Matrix world);
	Matrix world();

	void setTextureID(GLint);

	void setColor(Vector4 color);

protected:
	VertexDefinition* m_Vertices;
	GLushort* m_Indices;
	unsigned int m_NumberOfIndices;
	
	Shader* m_Shader;

	Matrix m_World;

	GLint m_TextureID;

	Vector4 m_Color;
	
};

#endif