#include "common.h"
#include "Material.h"

Material::Material()
{
	m_Ambient = Vector4(0.2, 0.2, 0.2, 1);
	m_Diffuse = Vector4(1, 1, 1, 1);
	m_Specular = Vector4(1, 1, 1, 1);
	m_SpecularPower = 20;
}

Material::~Material()
{

}

void Material::setAmbient(float r, float g, float b, float a)
{
	m_Ambient = Vector4(r, g, b, a);
}

void Material::setDiffuse(float r, float g, float b, float a)
{
	m_Diffuse = Vector4(r, g, b, a);
}

void Material::setSpecular(float r, float g, float b, float a)
{
	m_Ambient = Vector4(r, g, b, a);
}

void Material::setSpecularPower(float power)
{
	m_SpecularPower = power;
}

Vector4 Material::ambient()
{
	return m_Ambient;
}

Vector4 Material::diffuse()
{
	return m_Diffuse;
}


Vector4 Material::specular()
{
	return m_Specular;
}

float Material::specularPower()
{
	return m_SpecularPower;
}

void Material::setShader(Shader* shader)
{ 
	m_Shader = shader; 
}