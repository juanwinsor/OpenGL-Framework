#ifndef __MODEL_H
#define __MODEL_H

#include "common.h"

class Model
{
public:
	Model(){};
	~Model()
	{
		//delete VB/IBO
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);

		//delete the vertices if they've been set
		if(m_Vertices != NULL)
		{
			delete[] m_Vertices;
			delete[] m_Indices;
		}
	}

	bool Load(char* fileName);
	void CreateCube(float width, float height, float depth);

	VertexDefinition* Vertices();
	GLushort* Indices();
	int IndexCount();

	GLuint VBO();
	GLuint IBO();

	VertexDefinition* m_Vertices;
	GLushort* m_Indices;
	int m_IndexCount;


protected:
	

	//VBO and IBO
	GLuint m_VBO;
	GLuint m_IBO;
};

#endif