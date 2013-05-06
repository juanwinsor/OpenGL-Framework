#include "common.h"
#include "RenderableModel.h"
#include "Renderer.h"
#include <stddef.h>

void RenderableModel::LoadModel(char* filename)
{
	m_Model.Load(filename);

}

void RenderableModel::draw()
{
	glLoadIdentity();

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_Model.VBO());

	Shader* currentShader;

	//m_Shader->apply();
	if(m_LightingMode == LIGHTINGMODE_NONE)
	{
		//use shader that came with the material
		currentShader = m_Material->shader();	
	}
	else if(m_LightingMode == LIGHTINGMODE_NORMAL)
	{		
		//refresh the light values in the shader
		LightManager::getInstance()->update();
		//set the material for lighting
		LightManager::getInstance()->setMaterial(m_Material);
		//use the light shader
		currentShader = LightManager::getInstance()->shader();
	}

	// Set up the uniforms.
	glUniformMatrix4fv(currentShader->worldViewProjectionHandle(), 1, false, (GLfloat*)&Renderer::getInstance()->camera()->worldViewProjection(m_World));
	currentShader->setUniform("u_Projection", Renderer::getInstance()->camera()->projection());
	currentShader->setUniform("u_World", m_World);
	currentShader->setUniform("u_View", Renderer::getInstance()->camera()->view());

	currentShader->apply();		


	//
	//vertex position
	glVertexAttribPointer(currentShader->vsPositionHandle(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), (GLvoid*)offsetof(VertexDefinition, position));//(GLvoid*)offsetof(m_Model.Vertices(), position)); //&Verts->position);
    glEnableVertexAttribArray(currentShader->vsPositionHandle());
	//vertex color
	glVertexAttribPointer(currentShader->vsColorHandle(), 4, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), (GLvoid*)offsetof(VertexDefinition, color)); //m_Vertices->color); //&Verts->color);
    glEnableVertexAttribArray(currentShader->vsColorHandle());
	//uv coords
	glVertexAttribPointer(currentShader->vsUVCoordinateHandle(), 2, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), (GLvoid*)offsetof(VertexDefinition, uv));
    glEnableVertexAttribArray(currentShader->vsUVCoordinateHandle());
	//normals
	glVertexAttribPointer(currentShader->vsNormalHandle(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), (GLvoid*)offsetof(VertexDefinition, normal));
    glEnableVertexAttribArray(currentShader->vsNormalHandle());

	//set uniforms
	currentShader->setUniform("u_Color", Vector3(m_Color.x, m_Color.y, m_Color.z));

	//draw the elements
	//glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_SHORT, m_Model.Indices());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Model.IBO());
	glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glDisableVertexAttribArray(currentShader->vsPositionHandle());
    glDisableVertexAttribArray(currentShader->vsColorHandle());
	glDisableVertexAttribArray(currentShader->vsUVCoordinateHandle());
	glDisableVertexAttribArray(currentShader->vsNormalHandle());
	
}

void RenderableModel::setWorld(Matrix world)
{
	m_World = world;
}

Matrix RenderableModel::world()
{
	return m_World;
}

void RenderableModel::setTextureID(GLint textureID)
{
	m_TextureID = textureID;
}

void RenderableModel::setColor(Vector4 color)
{
	m_Color = color;
}

void RenderableModel::setMaterial(Material* material)
{
	m_Material = material;
}

void RenderableModel::setLightingMode(LightingMode lightingMode)
{
	m_LightingMode = lightingMode;
}

void RenderableModel::CreateCube(float width, float height, float depth)
{
	m_Model.CreateCube(width, height, depth);
}