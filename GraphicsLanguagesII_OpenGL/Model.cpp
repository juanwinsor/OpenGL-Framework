#include "common.h"
#include "Model.h"
#include "Utility\objloader\objLoader.h"


//bool Model::Load(char* fileName)
//{
//	//use the obj loader to load the mesh data
//	objLoader loader;
//	loader.load(fileName);
//
//	//setup the sizes of the data
//	m_Vertices = new VertexDefinition[loader.vertexCount];
//	m_Indices = new GLushort[loader.faceCount * 3];
//	m_IndexCount = loader.faceCount * 3;
//
//	//copy the vertex data from the loaded mesh
//	for(int i = 0; i < loader.vertexCount; i++)
//	{
//		m_Vertices[i].position[0] = loader.vertexList[i]->e[0];
//		m_Vertices[i].position[1] = loader.vertexList[i]->e[1];
//		m_Vertices[i].position[2] = loader.vertexList[i]->e[2];
//	}
//
//	//copy the index data from the loaded mesh
//	int pm = 0;
//	for(int i = 0; i < loader.faceCount; i++)
//	{
//		//premultiply
//		pm = i * 3;
//		m_Indices[pm] = loader.faceList[i]->vertex_index[0];
//		m_Indices[pm + 1] = loader.faceList[i]->vertex_index[1];
//		m_Indices[pm + 1] = loader.faceList[i]->vertex_index[2];
//
//		return false;
//	}
//
//}



bool Model::Load(char* fileName)
{

	objLoader mesh;

	mesh.load(fileName);

	//allocate face count * 3 vertdefs and indices
	//setup the sizes of the data
	m_IndexCount = mesh.faceCount * 3;
	m_Vertices = new VertexDefinition[m_IndexCount];
	m_Indices = new GLushort[m_IndexCount];
	//check facelist has 3 verts per face, and subdivide on 4 (handles only 3 and 4 verts per face)
	

	//loop from 0 to facecount
		//look from  0 to 3 vertices in each face
			//find the vertexpos for the vert, copy to vertdef
			//normal
			//uv
	float scale = 1 / 10.0f;
	int pm = 0;
	//loop through each face
	for(int i = 0; i < mesh.faceCount; i++)
	{
		pm = i * 3;
		//loop through each vertex in each face
		for(int j = 0; j < 3; j++)
		{
			//error check index counts

			m_Vertices[pm + j].position[0] = mesh.vertexList[mesh.faceList[i]->vertex_index[j]]->e[0] * scale;
			m_Vertices[pm + j].position[1] = mesh.vertexList[mesh.faceList[i]->vertex_index[j]]->e[1] * scale;
			m_Vertices[pm + j].position[2] = mesh.vertexList[mesh.faceList[i]->vertex_index[j]]->e[2] * scale;

			m_Vertices[pm + j].normal[0] = mesh.normalList[mesh.faceList[i]->normal_index[j]]->e[0];
			m_Vertices[pm + j].normal[1] = mesh.normalList[mesh.faceList[i]->normal_index[j]]->e[1];
			m_Vertices[pm + j].normal[2] = mesh.normalList[mesh.faceList[i]->normal_index[j]]->e[2];

			m_Vertices[pm + j].uv[0] = mesh.textureList[mesh.faceList[i]->texture_index[j]]->e[0];
			m_Vertices[pm + j].uv[1] = mesh.textureList[mesh.faceList[i]->texture_index[j]]->e[1];

			m_Vertices[pm + j].color[0] = 1;
			m_Vertices[pm + j].color[1] = 1;
			m_Vertices[pm + j].color[2] = 1;
			m_Vertices[pm + j].color[3] = 1;

			m_Indices[pm + j] = pm + j;
		}
	}




	//**************************************************VBO and IBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDefinition) * mesh.faceCount * 3, m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * mesh.faceCount * 3, m_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	return true;
}

VertexDefinition* Model::Vertices()
{
	return m_Vertices;
}

GLushort* Model::Indices()
{
	return m_Indices;
}

int Model::IndexCount()
{
	return m_IndexCount;
}

GLuint Model::VBO()
{
	return m_VBO;
}

GLuint Model::IBO()
{
	return m_IBO;
}

void Model::CreateCube(float width, float height, float depth)
{
	m_IndexCount = 36;
	m_Vertices = new VertexDefinition[24];
	m_Indices = new GLushort[m_IndexCount];

	float hw = width/2;
    float hh = height/2;
    float hd = depth/2;

    VertexDefinition vert2[24] =
    {
        // front face
        { -hw, -hh,  hd,   1,1,1,1,    0, 0,	0, 0, 1 },
        {  hw, -hh,  hd,   1,1,1,1,    1, 0,	0, 0, 1 },
        { -hw,  hh,  hd,   1,1,1,1,    0, 1,	0, 0, 1 },
        {  hw,  hh,  hd,   1,1,1,1,    1, 1,	0, 0, 1 },

        // back face
        { -hw, -hh, -hd,   1,1,1,1,    0, 0,	0, 0, -1 },
        {  hw, -hh, -hd,   1,1,1,1,    1, 0,	0, 0, -1 },
        { -hw,  hh, -hd,   1,1,1,1,    0, 1,	0, 0, -1 },
        {  hw,  hh, -hd,   1,1,1,1,    1, 1,	0, 0, -1 },

        // left face
        { -hw, -hh, -hd,   1,1,1,1,    0, 0,	-1, 0, 0 },
        { -hw,  hh, -hd,   1,1,1,1,    1, 0,	-1, 0, 0 },
        { -hw, -hh,  hd,   1,1,1,1,    0, 1,	-1, 0, 0 },
        { -hw,  hh,  hd,   1,1,1,1,    1, 1,	-1, 0, 0 },

        // right face
        {  hw, -hh, -hd,   1,1,1,1,    0, 0,	1, 0, 0 },
        {  hw,  hh, -hd,   1,1,1,1,    1, 0,	1, 0, 0 },
        {  hw, -hh,  hd,   1,1,1,1,    0, 1,	1, 0, 0 },
        {  hw,  hh,  hd,   1,1,1,1,    1, 1,	1, 0, 0 },

        // top face
        { -hw,  hh, -hd,   1,1,1,1,    0, 0,	0, 1, 0 },
        {  hw,  hh, -hd,   1,1,1,1,    1, 0,	0, 1, 0 },
        { -hw,  hh,  hd,   1,1,1,1,    0, 1,	0, 1, 0 },
        {  hw,  hh,  hd,   1,1,1,1,    1, 1,	0, 1, 0 },

        // bottom face
        { -hw, -hh, -hd,   1,1,1,1,    0, 0,	0, -1, 0 },
        {  hw, -hh, -hd,   1,1,1,1,    1, 0,	0, -1, 0 },
        { -hw, -hh,  hd,   1,1,1,1,    0, 1,	0, -1, 0 },
        {  hw, -hh,  hd,   1,1,1,1,    1, 1,	0, -1, 0 },
    };

    GLushort indices2[6*6] = {  0,  1,  2,  1,  2,  3,
                                4,  5,  6,  5,  6,  7,
                                8,  9, 10,  9, 10, 11,
                               12, 13, 14, 13, 14, 15,
                               16, 17, 18, 17, 18, 19,
                               20, 21, 22, 21, 22, 23, };

    for( int i=0; i<24; i++ )
    {
		m_Vertices[i] = vert2[i];
    }

    for( int i=0; i<36; i++ )
    {
		m_Indices[i] = indices2[i];
    }


	//**************************************************VBO and IBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDefinition) * 24, m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 36, m_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}