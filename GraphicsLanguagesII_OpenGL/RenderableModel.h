#ifndef __RENDERABLEMODEL_H
#define __RENDERABLEMODEL_H

#include "Renderable.h"
#include "Model.h"
#include "Shader.h"
#include "LightManager.h"
#include "Material.h"

class RenderableModel : public Renderable
{
public:
	RenderableModel()
	{
		m_LightingMode = LIGHTINGMODE_NORMAL;
		m_Color = Vector4(1, 1, 1, 1);
		m_TextureID = 0;
		m_World.SetIdentity();
		m_Material = NULL;
	}
	~RenderableModel(){}

	void LoadModel(char* filename);

	void draw();

	void setWorld(Matrix world);
	Matrix world();

	void setTextureID(GLint);

	void setColor(Vector4 color);

	void setMaterial(Material* material);
	Material* material(){ return m_Material; };

	void setLightingMode(LightingMode lightingMode);

	void CreateCube(float width, float height, float depth);

protected:
	Model m_Model;

	Matrix m_World;

	GLint m_TextureID;

	Vector4 m_Color;

	Material* m_Material;

	LightingMode m_LightingMode;
};

#endif