#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "Utility\Vector.h"
#include "Shader.h"

class Material
{
public:
	Material();
	~Material();

	void setShader(Shader* shader);
	Shader* shader(){ return m_Shader; };

	Vector4 ambient();
	Vector4 diffuse();
	Vector4 specular();
	float specularPower();

	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setSpecularPower(float power);

protected:
	Shader* m_Shader;

	Vector4 m_Ambient;
	Vector4 m_Diffuse;
	Vector4 m_Specular;
	float m_SpecularPower;
};

#endif